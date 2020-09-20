/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
 #ifndef MBED_TEST_MODE

#include "mbed.h"
#include "FATFileSystem.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include <math.h>
#include "SRF05.h"
#include "USBAudio.h"
#include "SDBlockDevice.h"
#include "AudioPlayer.h"
#include "WaveAudioStream.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_audio.h"

#define BUFFER_SIZE 512
#define FREQ_25_MHZ 25000000

#define SCRATCH_BUFF_SIZE  1024
#define RECORD_BUFFER_SIZE  4096
 
// Default network interface object. 
NetworkInterface *net = NetworkInterface::get_default_instance();


//Buffer state enum
typedef enum {
    BUFFER_OFFSET_NONE = 0,
    BUFFER_OFFSET_HALF = 1,
    BUFFER_OFFSET_FULL = 2,
} BUFFER_StateTypeDef;

//buffer state variable 
volatile uint32_t  audio_rec_buffer_state = BUFFER_OFFSET_NONE;


/*-------------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32f769i_discovery_audio.c file
           and their implementation should be done in the user code if they are needed.
  -------------------------------------------------------------------------------------*/
/**
  * @brief Manages the DMA Transfer complete interrupt.
  * @param None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
    audio_rec_buffer_state = BUFFER_OFFSET_FULL;
}
 
/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
    audio_rec_buffer_state = BUFFER_OFFSET_HALF;
}
 
/**
  * @brief  Audio IN Error callback function.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_Error_CallBack(void)
{
    printf("BSP_AUDIO_IN_Error_CallBack\n");
}
 
 
/**
  * @brief  Copy content of pbuffer2 to pbuffer1
  * @param1 BufferOut
  * @param2 BufferIn
  * @param3 Size
  * @retval None
  */
static void CopyBuffer(int16_t *pbuffer1, int16_t *pbuffer2, uint16_t BufferSize)
{
    uint32_t i = 0;
    for(i = 0; i < BufferSize; i++) {
        pbuffer1[i] = pbuffer2[i];
    }
}


//Initialize sensors connected to the pins

    // Connection for SD card
    SDBlockDevice sd(PB_15, PB_14, PA_12, PJ_0);//MOSI, MISO, SCLK, CS
    FATFileSystem fs("sd", &sd);

    // Proximity Sensor 
    SRF05 srf04_F(PH_6, PA_11); // ECHO (pin.9), TRIG (pin.10)
    SRF05 srf04_E(PB_8, PB_9); //ECHO (pin.15), TRIG (pin.14)
       

/**
    * @brief play the audio
    * @param1 isAdult
    * @retval -1 if error; 0 else 
    */
int playAudio(int a)
{
    // Set the maximum speed so it can keep up with audio
    sd.frequency(FREQ_25_MHZ);
    // Load WAV file from SD card
    // WAV file must be PCM signed 16-bit little endian

    //Opening file from sd card
    File file;

    //if a, then open file adult.wav; 
    //else open file child.wav
    if(a){
        //checking file opening
        if (file.open(&fs, "songs/adult.wav") != 0) {
            error("Could not open 'songs/adult.wav'\r\n");
            return -1;
        }
    }
    else{
        if (file.open(&fs, "songs/child.wav") != 0) {
            error("Could not open 'songs/child.wav'\r\n");
            return -1;
        } 
    }

    //"song" is the audio data object
    WaveAudioStream song(&file);

    // Check to see if file is a valid WAV file
    printf("Vedo se e\' valido\r\n");
    if (song.get_valid() == 0) {
        error("ERROR: not valid WAV file\r\n");
        return -1;
    }

    // WAV file must be 16-bit
    printf("Vedo se ha 16 bit\r\n");
    if (song.get_bytes_per_sample() != 2) {
        error("ERROR: WAV file not 2 bytes per sample (16-bit)\r\n");
        return -1;
    }

    //Preparing audio
    printf("Preparo la riproduzione dell\'audio\r\n");
    USBAudio audio(true, 8000, song.get_channels(), song.get_sample_rate(), song.get_channels());
    //array to store the chunk of song to be played at each time
    uint8_t buffer[BUFFER_SIZE];
    int num_bytes_read;
    printf("Playing Audio\r\n");
    
   

    //Initialize the audio device
    uint8_t ChannelNumber = BSP_AUDIO_IN_GetChannelNumber();
    if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 90, BSP_AUDIO_FREQUENCY_44K) == AUDIO_ERROR) {
        printf("BSP_AUDIO_OUT_Init error\n");
        return -1;
    }
    if(ChannelNumber > 2) {
        BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_0123);
    } else {
        BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
    }
    printf("initialized");
    
    
    file.read(buffer, BUFFER_SIZE);
    printf("read file once");
   
    //infinite loop for playing the audio
    while (1) {
        //read a buffer of the song
        num_bytes_read = song.read(buffer, BUFFER_SIZE);
        
        //check if song is over
        if (num_bytes_read <= 0) {
            printf("Song Over\r\n");
            //exit the loop
            break;
        }

        // Play the recorded buffer 
        if (BSP_AUDIO_OUT_Play((uint16_t *) &buffer, num_bytes_read) == AUDIO_ERROR) {
            printf("BSP_AUDIO_OUT_Play error\n");
            return -1;
        }
    }
    //Close the WAV file
    song.close();
    //Close the file
    file.close();
    return 0;
}


int main(void)
{
    printf("\nStarting ArTeller\n");

    // Connect to the Internet (DHCP is expected to be on)
    printf("Connecting to the network using the default network interface...\n");
    net = NetworkInterface::get_default_instance();
    nsapi_error_t net_status = NSAPI_ERROR_NO_CONNECTION;
    while ((net_status = net->connect()) != NSAPI_ERROR_OK) {
        printf("Unable to connect to network (%d). Retrying...\n", net_status);
    }
    printf("Connected to the network successfully. IP address: %s\n", net->get_ip_address());
    
    // MQTT 

    float version = 0.6;
    printf("HelloMQTT: version is %.2f\r\n", version);
    //mqtt topic for sending telemetry to our ThingsBoard's device
    char* topic = "v1/devices/me/telemetry";
    
    //connect to ThingsBoard's MQTT broker

    //create mqtt client object
    MQTTNetwork mqttNetwork(net);
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork); 

    // thingsboard broaker is accesible at demo.thingsboard.io; 
    // mqtt port we use is 1883
    const char* hostname = "demo.thingsboard.io";
    int port = 1883;
    printf("Connecting to %s:%d\r\n", hostname, port);
    //connect cliet to broker
    int rc = mqttNetwork.connect(hostname, port);
    //check connection
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);
    //send initializer data
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.clientID.cstring = "mbed";
    // tb access token 
    data.username.cstring = "NbIwSmfPyfdSZ81MpHyL";
    //check connection
    if ((rc = client.connect(data)) != 0) {
        printf("rc from MQTT connect is %d\r\n", rc);
    }
    printf("connesso\n");

    //mqtt message object
    MQTT::Message message;
    //threshold for the distance
    float threshold = 40;

    //counter for distnace
    int ctr1 = 0;
    int ctr2 = 0;

    //counters for adults and children detected in session
    int adulti = 0;
    int bambini = 0;

    //distances
    int dist1;
    float dist2;
    

    //create mqtt message to reset numero_adulti and numero_bambini in the ThingsBoard's dashboard
    char buffo[256];
    //create message payload
    int n = snprintf(buffo, sizeof(buffo), "{\"numero_adulti\":\"0\",\"numero_bambini\":\"0\"}");
    message.payload = reinterpret_cast<void*>(buffo);
    message.payloadlen = n;
    // send message
    printf("Mandando messaggio\n");
    rc = client.publish(topic, message);
    printf("Mandato messaggio\n");
    

    //infinite loop 
    while(1) {
        
        //read distances from both sensors
        dist1 = srf04_F.read();
        dist2 = srf04_E.read();
        
        //update counters
        if( dist1 < threshold){
            ctr1++;
        }
        else
            ctr1 = 0;
            
        if( dist2 < threshold){
            ctr2++;
        }
        else
            ctr2 = 0;
        
        printf("dist 1: %d\n",dist1); 
        printf("dist 2: %.0f\n",dist2);
        

        //send message and play audio for adult
        if(ctr1 == 8 && ctr2 > 5){
            //increment adulti counter
            adulti++;
            //create message payload
            char buf[256];
            int n = snprintf(buf, sizeof(buf), "{\"adulto\":\"adulto\",\"triggered\":\"adulto\",\"numero_adulti\":\"%d\"}",adulti);
            message.payload = reinterpret_cast<void*>(buf);
            message.payloadlen = n;
            //send message
            printf("Mandando messaggio\n");
            rc = client.publish(topic, message);
            printf("Mandato messaggio\n");
            printf("ADULTO\n");
            //play audio
            if(playAudio(1) == -1) printf("Error in playing audio");
            //reset counter
            ctr1 = 0;
            ctr2 = 0;
        }

        //send message and play audio for children
        else if(ctr1 == 8){
            //increment bambini couter
            bambini++;
            //create message payload
            char buf[256];
            int n = snprintf(buf, sizeof(buf), "{\"bambino\":\"bambino\",\"triggered\":\"bambino\",\"numero_bambini\":\"%d\"}",bambini);
            message.payload = reinterpret_cast<void*>(buf);
            message.payloadlen = n;
            //send message
            printf("Mandando messaggio\n");
            rc = client.publish(topic, message);
            printf("Mandato messaggio\n");
            printf("BAMBINO\n");
            //play audio
            if(playAudio(0) == -1) printf("Error in playing audio");
            //reset counter
            ctr1 = 0;
        }
        
        //wait 0.6 seconds
        wait(0.6);
    }

    mqttNetwork.disconnect();

    printf("Version %.2f: finish msgs\r\n", version/*, arrivedcount*/);

    return 0;


}

#endif /* MBED_TEST_MODE */

