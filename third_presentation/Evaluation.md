# Evaluation

# What we want to evaluate 

## Proximity Sensors
For this aspect of the project we will evaluate the following:
	
1. **Time for the detection**, the time period that occurs between the moment in which the user is front of the sensor and when its presence is detected. Measured in milliseconds. It would be considered a success if it is under 3 seconds.

2. **Number of false positives**, the system has to be triggered only if the person is interested in the statue. A person that is just walking nearby would not trigger the system. It is an heuristic measure, a good threshold could be at 80%

3. **Number of false negatives**, the system must be triggered if a user is standing in front of the camera sensor. It is an heuristic measure too, and a good threshold could be at 95%


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

## Overall cost of the system

# Results

## Proximity Sensors
1. **Time for the detection**,

2. **Number of false positives**,

3. **Number of false negatives**,

## Cloud infrastructure

1. **Latency**,

2. **Dashboard usability** , 

## User Experience

1. **The system is prevedible**

2. **The system is consistent**
	
3. **The system gives an appropriated feed-back**


## Overall cost of the system

# History
[First Delivery Evaluation](https://github.com/g185/ArTeller/blob/master/first_presentation/Evaluation.md)

[Second Delivery Evaluation](https://github.com/g185/ArTeller/blob/master/second_presentation/Evaluation.md)
