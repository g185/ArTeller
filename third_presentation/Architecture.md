# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture_3.jpg)

# IoT Edge Infrastructure
## Ultrasonic Proximity Sensor
![sensors](https://github.com/g185/SmartMuseum/blob/master/assets/sensors.jpg)

In order to detect the presence of a user, we are using HY-SRF05 proximity sensors. These are ultrasonic proximity sensors, with a 2cm-450cm distance detection range and 2mm of precision.
The retrieved proximity values are then sent to the STM32 Nucleo board.

## Speaker
Plays the audio description of the statue when the system is correctly triggered

## STM32 Nucleo board
![board](https://github.com/g185/SmartMuseum/blob/master/assets/discoF769ni.jpeg)


We are using an STM32F769I-DISCOVERY board, that offers the following advantages: 

- an ARM Cortex-M7 core

- Ethernet connector, used to connect it to the web in order to communicate with our cloud MQTT broker

- Audio line jacks, which is used for the audio outputs

- Four ST MEMS microphones, which we would like to take advantage of in yet to be implemented functionalities

- Arduino Uno V3 connectors, which are really helpful to connect the board with a large variety of cheap and easy to find sensors.


Processes the incoming proximity values to detect people. The system will start the activation protocol whenever it detects an interested user. In order to define an "interested" user, we will use an algorithm that will also detect the height of the visitor, in order to play a different audio track.



# Cloud Infrastructure
## Thingsboard
We will use Thingsboard MQTT broker in order to retrieve messages from the museum. we will then display them using the device dashboards that can be implemented with different widget and statistics from Thingsboard administrator. 


# History
[First Delivery Architecture](https://github.com/g185/ArTeller/blob/master/first_presentation/Architecture.md)


[Second Delivery Architecture](https://github.com/g185/ArTeller/blob/master/second_presentation/Architecture.md)
