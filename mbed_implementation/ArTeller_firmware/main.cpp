/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
 #ifndef MBED_TEST_MODE

#include "mbed.h"
//#include "simple-mbed-cloud-client.h"
#include "FATFileSystem.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include <math.h>
//proximity sensor
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
 
// Default network interface object. Don't forget to change the WiFi SSID/password in mbed_app.json if you're using WiFi.
NetworkInterface *net = NetworkInterface::get_default_instance();
// Default User button for GET example
InterruptIn button(BUTTON1);
// Default LED to use for PUT/POST example
DigitalOut led(LED1, 0);
DigitalOut led2(LED2, 0);
DigitalOut led3(LED3, 0);
// How often to fetch sensor data (in seconds)
#define SENSORS_POLL_INTERVAL 3.0

// Send all sensor data or just limited (useful for when running out of memory)
#define SEND_ALL_SENSORS
EventQueue eventQueue;



typedef enum {
    BUFFER_OFFSET_NONE = 0,
    BUFFER_OFFSET_HALF = 1,
    BUFFER_OFFSET_FULL = 2,
} BUFFER_StateTypeDef;
 
volatile uint32_t  audio_rec_buffer_state = BUFFER_OFFSET_NONE;

// Connection for SD card
//SDBlockDevice sd(R79, R80, R81, R82);
SDBlockDevice sd(PB_15, PB_14, PA_12, PJ_0);//MOSI, MISO, SCLK, CS
FATFileSystem fs("sd", &sd);




/*-------------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32f769i_discovery_audio.c file
           and their implementation should be done in the user code if they are needed.
           Below some examples of callback implementations.
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


/* Proximity Sensor */
    SRF05 srf04_F(PH_6, PA_11); // ECHO (pin.9), TRIG (pin.10)
    SRF05 srf04_E(PB_8, PB_9); //ECHO (pin.15), TRIG (pin.14)
    //SRF05 srf04_D(PJ_4, PB_15); // ECHO (pin.8), TRIG (pin.11)


int playAudio(int a)
{
    // Set the maximum speed so it can keep up with audio
    sd.frequency(FREQ_25_MHZ);
    // Load WAV file from SD card
    // WAV file must be PCM signed 16-bit little endian
    printf("Provo a pia il file\r\n");
    File file;
    if(a){
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
    WaveAudioStream song(&file);//"song" is the audio data object
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
    printf("Preparo la riproduzione dell\'audio\r\n");
    USBAudio audio(true, 8000, song.get_channels(), song.get_sample_rate(), song.get_channels());
    uint8_t buffer[BUFFER_SIZE];
    int num_bytes_read;
    printf("Playing Audio\r\n");
    
    uint8_t ChannelNumber = BSP_AUDIO_IN_GetChannelNumber();

        /* Initialize the audio device*/
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
    //uint16_t bufferone[BUFFER_SIZE/2];
    uint16_t bufferone[BUFFER_SIZE];
    // Reads and plays data from WAV file over USB until song is over
    while (1) {
        num_bytes_read = song.read(buffer, BUFFER_SIZE);
        //printf("%d\n\r",num_bytes_read);
        if (num_bytes_read <= 0) {
            printf("Song Over\r\n");
            break;
        }
        //printf("inizio for");
        /*for(int i = 0; i<510; i=i+2){
            printf("%d\n");
            uint8_t d1=buffer[i]; 
            uint8_t d2=buffer[i+1]; 
            bufferone[i/2] = (uint16_t)((d2 << 8) | d1);
        }*/
        /*for(int i = 0; i<512; i++){
            printf("%d\n\r",i);
            uint16_t a = 0x0f;
            uint8_t d1=buffer[i]; 
            bufferone[i] = (uint16_t)((a) & d1);
        }*/
        /* Play the recorded buffer */
        if (BSP_AUDIO_OUT_Play((uint16_t *) &buffer, num_bytes_read) == AUDIO_ERROR) {
            printf("BSP_AUDIO_OUT_Play error\n");
            return -1;
        }
    }
    song.close();//Close the WAV file
    file.close();
    return 0;
}


int main(void)
{
    printf("\nStarting Simple Pelion Device Management Client example\n");
    // Connect to the Internet (DHCP is expected to be on)
    printf("Connecting to the network using the default network interface...\n");
    net = NetworkInterface::get_default_instance();
    nsapi_error_t net_status = NSAPI_ERROR_NO_CONNECTION;
    while ((net_status = net->connect()) != NSAPI_ERROR_OK) {
        printf("Unable to connect to network (%d). Retrying...\n", net_status);
    }
    printf("Connected to the network successfully. IP address: %s\n", net->get_ip_address());

    
    
    /* Button try */
    DigitalIn pb(D8);
    pb.mode(PullUp);    //attiva il bottone
    wait(.001);
    int new_pb;
    int old_pb;
    
    /* MQTT */

    float version = 0.6;
    printf("HelloMQTT: version is %.2f\r\n", version);
    char* topic = "v1/devices/me/telemetry";

    MQTTNetwork mqttNetwork(net);

    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    
    const char* hostname = "demo.thingsboard.io";
    int port = 1883;
    printf("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);

    
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.clientID.cstring = "mbed";
    
    /* tb access token */
    
    //data.username.cstring = "UCZBC3Bwnt106OuZJISi";
    data.username.cstring = "NbIwSmfPyfdSZ81MpHyL";
    if ((rc = client.connect(data)) != 0) {
        printf("rc from MQTT connect is %d\r\n", rc);
    }
    printf("connesso\n");
    led2 = !led2;

    MQTT::Message message;
    float threshold = 40;
    bool triggered1 = false;
    int ctr1 = 0;
    int dist1;
    bool triggered2 = false;
    int ctr2 = 0;
    float pippo;
    float paperino;
    int adulti = 0;
    int bambini = 0;
    
    char buffo[256];
    int n = snprintf(buffo, sizeof(buffo), "{\"numero_adulti\":\"0\",\"numero_bambini\":\"0\"}");
    message.payload = reinterpret_cast<void*>(buffo);
    message.payloadlen = n;
    printf("Mandando messaggio\n");
    rc = client.publish(topic, message);
    printf("Mandato messaggio\n");
    
    while(1) {
        new_pb = pb;
        //se viene premuto il bottone
        if ((new_pb==0) && (old_pb==1)) {}
        
        dist1 = srf04_F.read();
        paperino = srf04_E.read();
        //pippo = srf04_D.read();
        
        //printf("la dist 2 e\' %.2f ma pippo e\' %.2f", srf04_D.read(), pippo);
        //printf("Paperino e\' %.2f", srf04_E.read());
        
        if( dist1 < threshold){
            ctr1++;
            
        }
        else
            ctr1 = 0;
            
        if( paperino < threshold){
            ctr2++;
            
        }
        else
            ctr2 = 0;
        
        printf("dist 1: %d\n",dist1); 
        printf("dist 2: %.0f\n",paperino);
        
        if(ctr1 == 8 && ctr2 > 5){
            adulti++;
            char buf[256];
            int n = snprintf(buf, sizeof(buf), "{\"adulto\":\"adulto\",\"triggered\":\"adulto\",\"numero_adulti\":\"%d\"}",adulti);
            message.payload = reinterpret_cast<void*>(buf);
            message.payloadlen = n;
            printf("Mandando messaggio\n");
            rc = client.publish(topic, message);
            printf("Mandato messaggio\n");
            printf("ADULTO\n");
            if(playAudio(1) == -1) printf("scaja");
            ctr1 = 0;
            ctr2 = 0;
            led3 = !led3;
        }
        else if(ctr1 == 8){
            bambini++;
            char buf[256];
            int n = snprintf(buf, sizeof(buf), "{\"bambino\":\"bambino\",\"triggered\":\"bambino\",\"numero_bambini\":\"%d\"}",bambini);
            message.payload = reinterpret_cast<void*>(buf);
            message.payloadlen = n;
            printf("Mandando messaggio\n");
            rc = client.publish(topic, message);
            printf("Mandato messaggio\n");
            printf("BAMBINO\n");
            if(playAudio(0) == -1) printf("scaja");
            ctr1 = 0;
            led3 = !led3;
        }
        
        //aggiornamento bottone
        old_pb = new_pb;
        wait(0.6);
        //pippo =0;
    }

    mqttNetwork.disconnect();

    printf("Version %.2f: finish msgs\r\n", version/*, arrivedcount*/);

    return 0;


}

#endif /* MBED_TEST_MODE */

