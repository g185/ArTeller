// ----------------------------------------------------------------------------
// Copyright 2016-2018 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------
#ifndef MBED_TEST_MODE

#include "mbed.h"
//#include "simple-mbed-cloud-client.h"
#include "FATFileSystem.h"
#include "LittleFileSystem.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include <math.h>
//proximity sensor
#include "SRF05.h"

// Default network interface object. Don't forget to change the WiFi SSID/password in mbed_app.json if you're using WiFi.
NetworkInterface *net = NetworkInterface::get_default_instance();

// Default block device available on the target board
BlockDevice *bd = BlockDevice::get_default_instance();

#if COMPONENT_SD || COMPONENT_NUSD
// Use FATFileSystem for SD card type blockdevices
FATFileSystem fs("fs");
#else
// Use LittleFileSystem for non-SD block devices to enable wear leveling and other functions
LittleFileSystem fs("fs");
#endif

// Default User button for GET example
InterruptIn button(BUTTON1);
// Default LED to use for PUT/POST example
DigitalOut led(LED1, 0);

// How often to fetch sensor data (in seconds)
#define SENSORS_POLL_INTERVAL 3.0

// Send all sensor data or just limited (useful for when running out of memory)
#define SEND_ALL_SENSORS

// Declaring pointers for access to Pelion Device Management Client resources outside of main()
/*MbedCloudClientResource *res_button;
MbedCloudClientResource *res_led;
MbedCloudClientResource *res_post;

// Additional resources for sensor readings
#ifdef SEND_ALL_SENSORS
MbedCloudClientResource *res_temperature;
MbedCloudClientResource *res_voltage;
#endif /* SEND_ALL_SENSORS */

// An event queue is a very useful structure to debounce information between contexts (e.g. ISR and normal threads)
// This is great because things such as network operations are illegal in ISR, so updating a resource in a button's fall() function is not allowed
EventQueue eventQueue;



int main(void)
{
    printf("\nStarting Simple Pelion Device Management Client example\n");

    int storage_status = fs.mount(bd);
    if (storage_status != 0) {
        printf("Storage mounting failed.\n");
    }

    // Connect to the Internet (DHCP is expected to be on)
    printf("Connecting to the network using the default network interface...\n");
    net = NetworkInterface::get_default_instance();

    nsapi_error_t net_status = NSAPI_ERROR_NO_CONNECTION;
    while ((net_status = net->connect()) != NSAPI_ERROR_OK) {
        printf("Unable to connect to network (%d). Retrying...\n", net_status);
    }

    printf("Connected to the network successfully. IP address: %s\n", net->get_ip_address());

    /* Proximity Sensor */
    SRF05 srf04_F(PH_6, PA_11); // ECHO (pin.9), TRIG (pin.10)
    
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


    MQTT::Message message;
    float threshold = 100;
    bool triggered = false;
    int ctr = 0;
    while(1) {
        new_pb = pb;
        //se viene premuto il bottone
        if ((new_pb==0) && (old_pb==1)) {}
        
        if(srf04_F.read() < threshold){
            ctr++;
        }
        else
            ctr = 0;
        
        
        
        
        
        if(ctr == 8){
            char buf[256];
            int n = snprintf(buf, sizeof(buf), "{\"triggered\":\"true\"}");
            message.payload = reinterpret_cast<void*>(buf);
            message.payloadlen = n;
            printf("Mandando messaggio\n");
            rc = client.publish(topic, message);
            printf("Mandato messaggio\n");
            ctr = 0;
        }
        
        //aggiornamento bottone
        old_pb = new_pb;
        wait(0.5);
    }

    mqttNetwork.disconnect();

    printf("Version %.2f: finish msgs\r\n", version/*, arrivedcount*/);

    return 0;


}

#endif /* MBED_TEST_MODE */
