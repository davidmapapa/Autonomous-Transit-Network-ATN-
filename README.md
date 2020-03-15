# ABSTRACT

 An Autonomous Transit Network **(ATN)** can be described as a system of podcars vehicle that operate under a common track, while each following their individual route. The system is autonomous due to the fact that there's no driving operator in the vehicle. But rather a centralize computer managing the flow of traffic and getting each client to their destination.

In such system, the podcars operate on an ELEVATED guideway or rails, avoiding traffic, buildings and natural habitats. Such system of vehicles are often referred to as Personal Rapid Transit **(PRT)**. Here are perfect illustration of such system by the [CGTN AMERICA news report](https://www.youtube.com/watch?v=QBp7HuzCCWU) and [Jpod's video](https://www.youtube.com/watch?v=rRIzvfW8XXs).
 
 In this project, I will describe the necessary steps needed in order to design, build and program a small scale podcar system. The pod system will run on a track with an inner and outter section (representing stations).
 
 After going through this tutorial you should be able to grasp the necessary code in order to program a single pod. [single pod video](https://player.vimeo.com/video/390130443).  

Once you obtain the necessary software skills you can add multiple pods and build your own system. [Two pods with collision avoidance video](https://www.youtube.com/watch?v=rCR6fW-CSME).

The 3D printing drawings and CAD necessary to build both the track and the vehicle can be found at www.jpods.com

Here will be listed the different electronics parts and related software to program the pods. Moreover, most of the code was performed on the Arduino IDE.
 
# TABLE OF CONTENTS 
##### 1.PCB and Microcontroller   
##### 2.Sensors   
##### 3.Code    
##### 4.Track  
##### 5.Debug  
 
 
 ## 1.PCB and Microcontroller: 
 
 The Printed Circuit Board (PCB) used in the podcar was specifically design by Jpods for this project. The board was design to fit an ESP LOLIN D32 board, a RASPBERRY PI, and multiple sensors. The board can be found at this link: [Board](https://drive.google.com/drive/u/0/folders/1CtqrttBD3XoiUPqs3ZEBOA0wLDOCQpJk).
 
 Once the board received, I soldered the different connectors (2 pins, 3 pins and 4 pins), resistors, capacitors, OPamp and the LOLIN D32 connectors. 

Here are pictures of an empty board, pins conncetors, resistors and capacitors before and after soldering. 
<img src="https://user-images.githubusercontent.com/58591461/74691817-32a8f080-5199-11ea-8c66-da995081eb52.jpg" width="350">
<img src="https://user-images.githubusercontent.com/58591461/74690625-95e45400-5194-11ea-99a9-ad1611ff258d.JPG" width="400">


Each board were then placed in a single podcar.  
<img src="https://user-images.githubusercontent.com/58591461/74691691-a696c900-5198-11ea-8146-19ac58ae621d.jpg" width="390">  <img src="https://user-images.githubusercontent.com/58591461/74691734-d34ae080-5198-11ea-8845-0f1f017e3e73.jpg" width="400">


## 2.Sensors: 

 In order to make a single pod operate autonomoulsy, different physical factors needed to be processed. This was done to ensure the safety and robustness of the system. Among those factos were the speed of the podcar vehicle, the front and back distances that seperates the vehicle from any objects, the distance travelled by the pod, whether the pod was in the inner or outter station and finally the position of other podcar vehicles.  

 To do so, we used few sensors that measured those aformentioned variables:
 -ultrasonic sensors
 -dc motor
 -servo motor
 -hall effect (on motor & track)
 -Neopixel
 -ESP camera
 -Raspberry pi
 -WiFi library
   
   #### a. Neopixel:
   
   
   #### b. Ultrasonic sensors:
   An ultrasonic sensor can be considered as 
    
   #### c. DC Motor:
     
   #### d. Servo Motor:
      
   #### e. Lolin D32:
   
   #### f. Hall Effect:
   
   #### g. ESP Camera:
   
   #### h. Raspberry Pi:
   
   #### i. WiFi LoLIN D32:
 



 

  
