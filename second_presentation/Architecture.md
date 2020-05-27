# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture_2.png)

# IoT Edge Infrastructure
## Ultrasonic Proximity Sensor
Retrieves proximity values and sends them to the STM32 Nucleo board

## Speaker
Plays the audio description of the statue when the system is correctly triggered

## STM32 Nucleo board
Processes the incoming proximity values to detect people. The system will start the activation protocol whenever it detects an interested user. In order to define an "interested" user, we will use an algorithm that will also detect the height of the visitor, in ordder to play a different audio track.

# Cloud Infrastructure
## AWS MQTT broker
We are using the MQTT broker provided by Amazon Web Services in order to retrieve messages from the museum. Using AWS IoT Core we will forward the information received to the different topics directly to DynamoDB.

## Persistence layer using DynamoDB
The database will be used in order to store information about every face detection, in particular the primary key will be the timestamp. In this way we will be able to generate some useful insights for the museum manager.

## Lambda processing (API gateway)
Using lambda functions we will be able to retrieve the information from DynamoDB and to create our metrics and statistics. Lambda functions are very flexible, thus we think that they are suitable for this task. The result of the lambda functions can be retrieved using API gateway.

## Serverless web application using React JS (S3 Bucket)
We will build a serverless web application built involving API gateway REST calls. For this task we will use React JS and this whole system will be hosted on amazon S3 buckets.
We will build an authorized access in order to make the contained statistics available for the museum manager.
