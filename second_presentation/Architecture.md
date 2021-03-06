# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture_2.png)

# IoT Edge Infrastructure
## Ultrasonic Proximity Sensor
Retrieves proximity values and sends them to the STM32 Nucleo board

## Speaker
Plays the audio description of the statue when the system is correctly triggered

## STM32 Nucleo board
Processes the incoming proximity values to detect people. The system will start the activation protocol whenever it detects an interested user. In order to define an "interested" user, we will use an algorithm that will also detect the height of the visitor, in order to play a different audio track.

# Cloud Infrastructure
## Thingsboard
We will use Thingsboard MQTT broker in order to retrieve messages from the museum. we will then display them using the device dashboards that can be implemented with different widget and statistics from Thingsboard administrator. 
