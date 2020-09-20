# Evaluation

# What we want to evaluate 

## Proximity Sensors
For this aspect of the project we will evaluate the following:
	
1. **Time for the detection**, the time period that occurs between the moment in which the user is front of the sensor and when its presence is detected. Measured in milliseconds. It would be considered a success if it is under 3 seconds.

2. **Number of false positives**, the system has to be triggered only if the person is interested in the statue. A person that is just walking nearby would not trigger the system. It is an heuristic measure, a good threshold could be at 80%

3. **Number of false negatives**, the system must be triggered if a user is standing in front of the camera sensor. It is an heuristic measure too, and a good threshold could be at 85%


## Cloud infrastructure
The cloud infrastructure we are using is based on ThingsBoard. This service provides us a cloud-based MQTT broker, and the possibility to develop easily a  smart looking dashboard that provides all the useful informations to the user.
For this aspect of the project we will evaluate the following:
	
1. **Latency**, The remote broker must be fast in order to generate insights for the museum manager. Latency is the time occurring between an audio execution and the insertion of the event in the database. It is measured in minutes and an acceptance threshold could be 1 minute

2. **Dashboard usability** , We want our dashboard to be usable and understandable by our target users


## User Experience
To evaluate the user experience we will use a review based method on  controlled experiments performed with the help of some potential users.
Some heuristics will be:

1. **The system is prevedible**

2. **The system is consistent**
	
3. **The system gives an appropriated feed-back**

## Multile devices
We want to evaluate whever our cloud MQTT broker is capale of working even when multiple devices are sending messages to it.

## Overall cost of the system
We want to evaluate the cost of our system.

# Results

## Proximity Sensors
1. **Time for the detection**, We conducted numerous hands-on experiment to empirically determine a time range that could be feasible for our user case, and we determine it to be 4 seconds long.

2. **Number of false positives**, We conducted 300 measurements as a test, and actually never experienced a false positive measurement. 

3. **Number of false negatives**,We conducted 300 measurements as a test, and experienced 28 false negative measurements, which was better than our prescribed goal of it being under 85%. 


## Cloud infrastructure

1. **Latency**, We tested the latency of our system under different circumstances, and found out it to be consistently under 1 second.

2. **Dashboard usability** , we conducted a controlled experiment involving users with the same technological skills as our potential users, and from it we extracted some suggestions for the design of our dashboard, like the use of charts and visual representation of data.

## User Experience

The controlled experiments we conducted with potential users of the system. The feedbacks we received are generally positive and the system respected the heuristics we took under consideration. However, we also received some suggestions for possible problematics and functionalities that can be implemented. One of which was the possibility to stop in some way the audio, once it has started.

## Multiple devices
We created a demo that utilizes a python script to simulate the presence of multiple devices sending messages to our ThingsBoard's broker. This demo was done to test the scalability of our project. From our tests we understood that ThingsBoard is fully capable of work without any issues with multiple devices.  

## Overall cost of the system

The board we used has a cost of around 45.However, since we ended up not taking advantage it brings, like the internal SD card reader (which was broken) and the ARM cortex, we could have used a cheaper device. The cost of our HY-SRF05 sensors is of around 2,50€ each; while the SD card reader is of around 7€. 

The cloud infrastructure is actually free.


# History
[First Delivery Evaluation](https://github.com/g185/ArTeller/blob/master/first_presentation/Evaluation.md)

[Second Delivery Evaluation](https://github.com/g185/ArTeller/blob/master/second_presentation/Evaluation.md)
