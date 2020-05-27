# Architecture

![architecture](https://github.com/g185/SmartMuseum/blob/master/assets/architecture_2.png)

# IoT Edge Infrastructure
## 
Retrieves images and sends them to the STM32 Nucleo board

## Speaker
Plays the audio description of the statue when the system is correctly triggered

## STM32 Nucleo board
Processes the incoming images to detect faces. The system will start the activation protocol whenever it detects an interested face. In order to define an "interested" face, we will adjust different parameters for example distance or detection time.

After detection, it will check if any of the nearby statues is currently speaking. If it is not the case, it will wait and listen for MQTT messages for a time interval of 2t (where t is the round trip time of MQTT messages from nearby statues). If it has not received anything, it will send an MQTT message on his own topic and it will proceed to play the audio description.

## Local MQTT broker
It handles every local exchanged message between different STM32 Nucleo boards. Through this element, every board will subscribe to the topics of nearby statues (because if they transmit the audio description simultaneously, interference may happen). We decided to include a local MQTT broker (instead of using only the remote one) in order to reduce latency. Furthermore, this component will forward every received message to the AWS MQTT broker.

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
