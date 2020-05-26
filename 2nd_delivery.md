# 2nd Delivery

## Comments received and decisions

-*Is face recognition too much for proximity?*
Even if face recognition was a challenging part of our project, we decided that it was really an utopy to run it on a constrained device without really long latency time. We decided to use proximity sensors that were better under a lot of perspectives.

-*Customization for kids vs adults could be a nice feature.*
Sure, it will be an important part of our project. The function that detects heights of the user is born to give a different audioguide to the kids. "Message in the bottle" functionalities will be an important feature for kids interactivity.

-*Include the designer in the README.*
We did it.


## Changes made to design, architecture and evaluation plan since 1st delivery
Design: The design was impacted by the decision to change sensors. We now will use proximity sensors in order to detect the presence of people. In order to have a different audioguide for kids we will detect height of the user. The motivations for this choiche are different: The difficulty of face recognition would lead the processing to last too much time, 

We also introduced the functionality "Message in the bottle" so that the users will be able to leave a short audiomessage to the next visitors. 

Architecture:
We decided to move from AWS to rom aws to thingsboard. now possibility for manager to access local mqtt to change audio and we have now local mqtt

Evaluation: evaluation of the proximity sensor 
thingsboard backend.


## Brief presentation of the technical work done since 1st delivery

-mqtt on stm32

-connection to thingsboard

-proximity sensor interface

-proximity sensor algorithm

-funzionamento bottomi

## List of functionalities that are missing and will be completed for the final delivery

-dashboard ciotta

-Manager che se connette e mette la roba sua

-miglioramenti a tutto

-now the board distinguish from kid to adult  and plays different tracks da finire


## Evaluation conducted since the 1st delivery

-evaluated sensors accuracy and other and board


## Expected evaluation for the final delivery

-quelle che mancane
