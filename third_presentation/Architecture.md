# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture_3.jpg)

The architecture of the project can be viewed in the scheme above. It is a simplified version in order to distinguish the different elements that compose our system. The following is just to understand the network and architecture, a more focused approach on hardware can be seen in the following chapter.

We can distinguish the main Board, in our case STM32F769NI-DISCOVERY, that is the main component of our IoT system. This board is able to process data that arrives from the two proximity sensors.

The proximity sensors are HY-SRF05 and use an ultrasonic system in order to detect proximity.

The data that arrives on the board is the main information and is processed using an algorithm that makes us able to detect the presence of people in front of the statues.Once the system is triggered in one way by one type of user, the board starts to play an audio track associated with the type of user that triggered. The output is emitted using the AUX cable and can be compatible with every speaker available right now.

Another important part of our system board regards the connection to the MQTT broker.

Once it is triggered, the system other than playing the audioguide, sends a message to an MQTT broker using a LAN cable. This MQTT broker is Thingsboard, that offers a stable and easy to use interface to create dashboards and to visualize and analyze data. A deeper look at the code and functionality of the different functions we used to connect to Thingsboard can be found in the section regarding Services and Software.

# IoT Edge Infrastructure

## STM32 Discovery board
![board](https://github.com/g185/SmartMuseum/blob/master/assets/discoF769ni.jpeg)


We are using an STM32F769I-DISCOVERY board, that offers the following advantages: 

- an ARM Cortex-M7 core

- Ethernet connector, used to connect it to the web in order to communicate with our cloud MQTT broker

- Audio line jacks, which is used for the audio outputs

- Four ST MEMS microphones, which we would like to take advantage of in yet to be implemented functionalities

- Arduino Uno V3 connectors, which are really helpful to connect the board with a large variety of cheap and easy to find sensors.


Processes the incoming proximity values to detect people. The system will start the activation protocol whenever it detects an interested user. In order to define an "interested" user, we will use an algorithm that will also detect the height of the visitor, in order to play a different audio track.

## Ultrasonic Proximity Sensor
![sensors](https://github.com/g185/SmartMuseum/blob/master/assets/sensors.jpg )

In order to detect the presence of a user, we are using HY-SRF05 proximity sensors. These are ultrasonic proximity sensors, with a 2cm-450cm distance detection range and 2mm of precision.
The retrieved proximity values are then sent to the STM32 Nucleo board.

## Speaker
We utilize a speaker connected with an AUX cable to our board's built-in audio line jack. Therefore it is controlled by the board.

## SD Card Reader

![sensors](https://github.com/g185/SmartMuseum/blob/master/assets/SD-card-read.jpg )

We utilize an external SD Card Reader, connected to the board with Arduino connection. We decided to use an external reader instead of the built-in one our board is equipped with, since it gave us multiple problems with software compatibilities with mbed-os and the external libraries we are using for the other functionalities of our system.

On the SD Card, is stored a Fat File System that contains the audio .wav files we need to play. Whenever we need to play an audio, the required file is retrieved from the SD card  and played through the audio jack output line in our board.


# Cloud Infrastructure
## Thingsboard
We will use Thingsboard MQTT broker in order to retrieve messages from the museum. we will then display them using the device dashboards that can be implemented with different widget and statistics from Thingsboard administrator. 
Values will be used for computing useful insights, in particular for what concerns the opera’s engagement rate (for example interacting visitors per hour). The result of this step will also be visible on the same dashboard



# History
[First Delivery Architecture](https://github.com/g185/ArTeller/blob/master/first_presentation/Architecture.md)


[Second Delivery Architecture](https://github.com/g185/ArTeller/blob/master/second_presentation/Architecture.md)
