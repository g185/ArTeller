# Design

In the following Mark Down document we have collected different User Personas and Storyboards for our Smart Museum project.
## Description
The aim of ArTeller is to provide a free audioguide service to the Sapienza Museum visitors, while providing useful insights to the museum manager. We believe that this service will make the museum visit more interesting and interactive, particularly for students and kids.

The idea consists in locating a device in proximity of each statue which will look for interested people through face detection. 
Our goal is to make this detection accurate as it can be, in order to avoid the people not interested to trigger the system.

We will also implement a priority queue between statues that are located nearby, in order to avoid sounds from different speakers overlapping.

Once the system is triggered by interested visitors, lt will start to play the audiodescription for the given opera. A web application will be accessible by the museum manager in order to retrieve meaningful statistics about the different engagement rates of the operas.

## User Personas

1. 23 yo female Art student "Annah".
She attends Art at Sapienza University and wants to see the sculptures she is studying from a closer point of view. 
![Annah](https://github.com/g185/SmartMuseum/blob/master/assets/Annah.jpg)

![Annah2](https://github.com/g185/SmartMuseum/blob/master/assets/Annah2.jpg)



2. 50 yo female museum manager "Margherita".
She manages the museum and is interested in the appeal offered by the different sculptures.  
![Margherita](https://github.com/g185/SmartMuseum/blob/master/assets/Margherita.jpg)
![Margherita2](https://github.com/g185/SmartMuseum/blob/master/assets/Margherita2.jpg)


3. 14 yo male student "Simone".
He is in a school trip at the museum. As every teenager he loves to be able to interact with everything using her smartphone.
![Simone](https://github.com/g185/SmartMuseum/blob/master/assets/Simone.png)

![Simone2](https://github.com/g185/SmartMuseum/blob/master/assets/Simone2.jpg)

## Storyboards 

1. Margherita has a new statue and has to place it in a Museum room. In this room there is no place for another statue, so she needs to understand which one of the current operas is less interesting from the point of view of the visitors. She uses the statistics displayed in the application in order to decide which one she can replace. Once she sees that statue_1 produces less interest, she replaces it with the new statue.
![Storyboard1](https://github.com/g185/SmartMuseum/blob/master/assets/Storyboard1.jpg)

2. An elementary school class is on a school trip at the museum. The kids, as always, don't show interest in the artworks, and are very distracted.. This untill one of the statue starts to talk and tell them its story, making thew experience more interactive and producing curiosity.
![Soìtoryboard2](https://github.com/g185/SmartMuseum/blob/master/assets/Storyboard2.png)
