# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture.png)

# IoT Edge Infrastructure
## Ultrasonic proximity sensor
Retrieves proximity and sends them to the STM32 Nucleo board

## Speaker
Plays the audio description of the statue when the system is correctly triggered

## STM32 Nucleo board
Processes the incoming proximity values to detect people standing nearby. The system will start the activation protocol whenever it detects an interested person. In order to define an "interested" person we will use a simple algorithm. The system will be able to detect kids from adults and play different audiodescriptions.

# Cloud Infrastructure
## Thingsboard 
Using the MQTT services to create a Dashboard. Thingsboard is an easyt to use with possibility to create multiple devices and displòay their values using differents widgets.
