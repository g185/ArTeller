# Evaluation

## Face Recognition
For this aspect of the project we will evaluate the following:
	
1. **Face Recognition Speed**, the time period that occurs between the moment in which the user is front of the camera and when the face is detected. Measured in milliseconds. It would be considered a success if it is under 2000ms

2. **Number of false positives**, the system has to be triggered only if the person is interested in the statue. A person that is just walking nearby would not trigger the system. It is an heuristic measure, a good threshold could be at 80%

3. **Number of false negatives**, the system must be triggered if a user is standing in front of the camera sensor. It is an heuristic measure too, and a good threshold could be at 90%

## Speakers
For this aspect of ArTeller we will evaluate the following:

1. **Loudness of the speaker**, measured in dB. The speaker must not be too loud in order to not annoy uninterested people, heuristic measure
	
2. **Interferences among multiple speakers**, Nearby speakers must not interfere with each other, it is an heuristic measure. This should be guaranteed by our priority management algorithm
	
## Local MQTT
Concerning the MQTT part, we will evaluate the following:

1. **Latency**, The local broker must be fast in order to execute our priority algorithm in a responsive way, latency is the time occurring between a detection and the nearby statues receiving the MQTT message. It is measured in milliseconds and an acceptance threshold could be 200 ms (MosquiTTo guarantees less than 10 ms delay between the publisher and the MQTT broker)
	
## AWS Backend
For what regards the AWS based backend we will evaluate the following:
	
1. **Latency**, The remote broker must be fast (though not as fast as the local one) in order to generate insights for the museum manager. Latency is the time occurring between an audio execution and the insertion of the event in the database. It is measured in minutes and an acceptance threshold could be 1 minute

## Test
In order to test our solution, since we cannot have access to real devices due to the Covid-19 emergency, we will proceed in this way:

	1. Face Recognition: we will test our face recognition technology using the webacams on our laptops.

	2. MQTT architecture: we will test the MQTT architecture using Iot-Lab

	3. Cloud infrastructure: deployed on AWS
	
## User Experience
To evaluate the user experience we will use a review based method oh a questionary that will be handed to visitors at the end of the museum visit.
Some heuristics will be:

	1. The system is prevedible
	
	2. The system is consistent
	
	2. The system gives an approvated feed-back
