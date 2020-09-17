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


We evaluated the possibility to use the camera, and we excluded it for the reasons i anticipated above.

We evaluated the proximity sensors, the distance and the latency.

We evaluated the latency of device to thingsboard MQTT message using ethernet connection.

## Expected evaluation for the final delivery

For the proximity sensors aspects we will evaluate: time for the detection, number of false positives and false negatives.

For the Speaker we will measure: Loudness of the speaker, measured in dB


