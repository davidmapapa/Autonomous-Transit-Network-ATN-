# ABSTRACT

 An Autonomous Transit Network can be described as a system of podcars (vehicle) that operate under a common track while each following their individual route. The system is labeled autonomous because no driving operator stir the cars, but instead a centralize computer manage the flow of traffic depending on each client's destination. In such system, the podcars operate on an ELEVATED guideway avoiding traffic, buildings and natural habitats. Such system of pod cars are often referred to as Personal Rapid Transit (PRT). 
 
 In the project bellow I will describe the steps needed to design and program a single pod to run on a track. The pod will switch from the inner to the outter station of the track, through the random function generated by the code or a webrowser page controlled by thhe user. 

Building such pod will require both hardware and software skills, which will be explained in detail in this project.    
 
# TABLE OF CONTENTS 
1.PCB and Microcontroller   
2.Sensors   
3.Code    
4.Track  
5.Debug  
 
 
 ## 1.PCB and Microcontroller: 
 
 The Printed Circuit Board (PCB) used in the podcar was specifically design by Jpods to work for this specific project. The board was design to fit a ESP LOLIN D32 board, a RASPBERRY PI, and multiple sensors. The board can be found at this link:
 
 Once the board received, I soldered the different connectors (2 pins, 3 pins and 4 pins), resistors, capacitors, OPamp and the LOLIN D32 board holder. 

Here are pictures of an empty board, pins conncetors, resistors and capacitors before and after soldering. 
<img src="https://user-images.githubusercontent.com/58591461/74690625-95e45400-5194-11ea-99a9-ad1611ff258d.JPG" width="400">
<img src="https://user-images.githubusercontent.com/58591461/74691817-32a8f080-5199-11ea-8c66-da995081eb52.jpg" width="350">


A detailed video of the steps to build the board can be found at this link:


Each board were then placed in a single podcar.

<img src="https://user-images.githubusercontent.com/58591461/74691691-a696c900-5198-11ea-8146-19ac58ae621d.jpg" width="350"><img src="https://user-images.githubusercontent.com/58591461/74691734-d34ae080-5198-11ea-8845-0f1f017e3e73.jpg" width="400">




## 2.Sensors: 

 In order to make a single pod operate autonomoulsy, it needs to be able to process certain factors. Once those parameters are processed each pod can make processed decisions and at the same time ensure safety and efficiency. The important factors that each pod needs to know are the front, back and side distances that seperates it from any objects, the speed at which it is travelling, the distance travelled, whether it has switch from an inner to an outter station and finally the position of other pods. 

 To do so, we used few sensors that measured those aformentioned variables. Therefore the sensors used per pod were:
 -ultrasonic sensors
 -dc motor
 -servo motor
 -hall effect (on motor & track)
 -Neopixel
 -ESP camera
 -Raspberry pi
 



 

  
