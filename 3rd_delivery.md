# 3rd Delivery

## Comments received and decisions

- *Focus on main functionalities, Customization for kids and adults*
We left the not influent functionalities as Pasquino,leaving them in Future Projects. We focused on the main feature that is the customization for kids in order 
to do a more precise and concise work.

## Changes made to design, architecture and evaluation plan since 1st delivery
Design: Design of the project was not impacted during this delivery. The functionalities remained the same, since we focused more on implementation.

Architecture:
The architecture received minor changes during implementation.
- The buttons for registration, that we implemented in order to register the message vocally, have been discharged in favour of a more feasible and dinamic 
approach given by the SD card.
Using an SD card makes possible to use an high quality audio track and a larger file dimention; furthemore in case of alimentation problems the audio tracks 
would be eliminated and with SD card this problem is not happening.
Also the little dimention of the internal memory was not enough to contain long audio tracks.

- The SD card reader integrated into the board produced different problems, and after 5 days of temptatives we decided to buy a new SD external reader. 
This device can be connected using SPI pins and is well integrated with mbed-os.

Evaluation: 
We changed the evaluation document in the following way:
- We decided to not perform tests on the speaker, since the audio output is dependent on the real ambient and we don't know which thresholds we can use.

- We added the results of the tests we did on the different metrics

- We did controlled experiments and collected useful data on user experience.

## Brief presentation of the technical work done since 2nd delivery

We started with the implementation of the user classification. This implies the use of a second sensor in order to have a better picture of the user that is in front
of the statue. The second sensor is positioned in a different height and makes possible to detect the presence of an adult. When triggered, the system will now send data 
about the fact that the user is a child or an adult. 

This data is now shown in a better looking format on the Thingsboard dashboard, that we implemented with the possibility to offer useful data and insights
about the visitors. The widgets of Thingsboard's dashboard now show the last detected user, a real-time average number of visitors and two charts that show the number of overall
children and adults that have triggered the sistem.

Bug fixing on ethernet connection, that we experced during tests and fixed using mbed-os new firmware

The main difficulties that we experienced were caused by the internal sd card reader. We realized that it was broken, so we decided to buy a new reader.
The integration of the new device FINISCI QUI

Another important improvement to our sistem concern the implementation of the audio output. The wav files that are present in the SD card, when the sistem is triggered,
are now sent via the aux output to an external speaker.


## Brief presentation of the evaluation conducted since the 2nd delivery

- Proximity Sensors
	
1. **Time for the detection**, the time period that occurs between the moment in which the user is front of the sensor and when its presence is detected. 

2. **Number of false positives**, the system has to be triggered only if the person is interested in the statue.

3. **Number of false negatives**, the system must be triggered if a user is standing in front of the camera sensor. 

- Cloud infrastructure
	
1. **Latency**, The remote broker must be fast in order to generate insights for the museum manager.

2. **Dashboard usability** , We want our dashboard to be usable and understandable by our target users.


- User Experience

The controlled experiments we conducted with potential users of the system. The feedbacks we received are generally positive and the system respected the heuristics we took under consideration. However, we also received some suggestions for possible problematics and functionalities that can be implemented. One of which was the possibility to stop in some way the audio, once it has started.

- Overall cost of the system

The board we used has a cost of around 45.However, since we ended up not taking advantage it brings, like the internal SD card reader (which was broken) and the ARM cortex, we could have used a cheaper device. The cost of our HY-SRF05 sensors is of around 2,50€ each; while the SD card reader is of around 7€. 

The cloud infrastructure is actually free.

## A brief list of the functionality that is still missing and which you aspect you did not manage to evaluate

- Pasquino
 A possible functionality of the systemis the possibility for the users to leave audio messages to the statue.
Thanks to the microphone equipped on our board, the museum visitors would be able to leave audio messages by simply clicking a button, and to play the latest message left from other users. by clicking a different button.
We still need to fully evaluate the feasibility of this functionality (especially in terms of possible bad behaviours from the users) before implementing and testing it.

- Possibility to stop
After out controlled experiments we received some important feedback and questions to stop the audio player. A possible solution might be the implementation of a button that stops the audio player. This problem is not correlated with false positives of the sensors, in fact this kind of problem didn't emerge in our tests, but more with the fact that sometimes the user could trigger involountarily the audio player and wants to stop the long audioguide.

- Real Users Questionnaire
An evaluation that we didn't apply is the use of questionnaires on real visitor of the sapienza museum, for evident problems of logistics and time. 



