# ABSTRACT

 An Autonomous Transit Network **(ATN)** can be described as a system of podcars vehicle that operate under a common track, while each following their individual route. The system is autonomous due to the fact that there's no driving operator in the vehicle. But rather a centralize computer managing the flow of traffic and getting each client to their destination.

In such system, the podcars operate on an elevated guideway or rail, thus avoiding traffic, buildings and natural habitats. Such system of vehicles are often referred to as Personal Rapid Transit **(PRT)**. Here are perfect illustration of such system by the [CGTN AMERICA news report](https://www.youtube.com/watch?v=QBp7HuzCCWU) and [Jpod's video](https://www.youtube.com/watch?v=rRIzvfW8XXs).
 
 In this project, I will describe the necessary steps needed in order to design, build and program a small scale podcar system. The pod system will run on a track with an inner and outter section (representing stations).
 
 After going through this tutorial you should be able to grasp the necessary code in order to program a single pod. [single pod video](https://player.vimeo.com/video/390130443).  

Once you obtain the necessary software skills you can add multiple pods and build your own system. [Two pods with collision avoidance video](https://www.youtube.com/watch?v=rCR6fW-CSME).

The 3D print drawings and CAD necessary to build both the track and the vehicle can be found at www.jpods.com

Here will be listed the different electronics parts and the Arduino files necessary to program the pods. 
 
# TABLE OF CONTENTS 
##### 1.PCB and Microcontroller   
##### 2.Sensors   
##### 3.Code    

 
 
 ## 1.PCB and Microcontroller: 
 
 The Printed Circuit Board (PCB) used in the podcar was specifically design by Jpods for this project. The board was design to fit an ESP LOLIN D32 board, a RASPBERRY PI, and multiple sensors. The board's link can be found by clicking below: [Board](https://drive.google.com/drive/u/0/folders/1CtqrttBD3XoiUPqs3ZEBOA0wLDOCQpJk). 
 
 Once the board received, I soldered the different connectors (2 pins, 3 pins and 4 pins), resistors, capacitors, OPamp and the LOLIN D32 connectors. A video of me assembling the board from scratch will be linked afterwards. 

Here are pictures of an empty board, pins conncetors, resistors and capacitors before and after soldering. 
<img src="https://user-images.githubusercontent.com/58591461/74691817-32a8f080-5199-11ea-8c66-da995081eb52.jpg" width="350">
<img src="https://user-images.githubusercontent.com/58591461/74690625-95e45400-5194-11ea-99a9-ad1611ff258d.JPG" width="400">


Each board was placed in a single podcar.  
<img src="https://user-images.githubusercontent.com/58591461/74691691-a696c900-5198-11ea-8146-19ac58ae621d.jpg" width="390">  <img src="https://user-images.githubusercontent.com/58591461/74691734-d34ae080-5198-11ea-8845-0f1f017e3e73.jpg" width="400">



## 2.Sensors: 

 In order to make a single pod operate autonomoulsy, different physical factors needed to be processed. This was done to ensure the safety and robustness of the system. Among those factors were the speed of the podcar vehicle, the front and back distances that seperating the vehicles from each other, the distance travelled by each vehicle, the station of each pod vehicle (inner or outter station) and finally the position of other podcar vehicles.  

 To do so, we used few sensors that measured those aformentioned variables:  
   #### a. Neopixel:
   Those are a string of LED located in front of the car in order to report the status of the vehilce. **Green** if there's no obstacle, **Red** if there's obstacle in front of the vehicle and **Blue** for obstacles in the back.
   <img src="https://cdn-shop.adafruit.com/1200x900/1426-00.jpg" width="350">
   
   
   #### b. Ultrasonic sensors:
   An ultrasonic sensor can be considered as an electronic device that measure the distance of an object using ultrasonic waves. The ultrasonic sensor sends a wave signals through a Ping and accounts for the time it takes for the wave to hit an object and bounce back. Knowing the speed at which a ultrasonic wave travel, it easy to determine the distance at which the object is located. 
   
   <img src="https://images-na.ssl-images-amazon.com/images/I/71-TKtOybqL._SL1500_.jpg" width="350">
    
   #### c. DC Motor:
   A DC Motor is an actuator device that converts electric current into mechanical energy. That energy is represented in terms of speed. 
   
   <img src="https://www.wiltronics.com.au/wp-content/uploads/images/make-and-create/gear-motor-dc-toy-car-wheel-arduino.jpg" width="350">
    
   
   
     
   #### d. Servo Motor:
   A servo motor is also an actuator device, that can precisely control its linear position, velocity and acceleration. A servo motor is a motor that has a build in closed-loop system. Meaning the postion of the motor can be determined using position feedback control. 
   
   <img src="https://media.digikey.com/Photos/DFRobot/MFG_SER0006.jpg" width="350" >
   
      
   #### e. Lolin D32:
   Lolin D32 is a microcontroller chip that is part of the WEMOS ESP32 microcontroller family. The chip is compatible with the Arduino IDE as well as micropython. A major benefit of the chip is that it easily allows WiFi connection.
   
   #### f. Hall Effect:
   An Hall effect sensor is a device that is able to detect a magnetic field. Therefore, one can use an hall sensor to detect magnets that are located at close proximity. We will use two different type of hall sensor, a latching sensor (left) that would detect small magnets placed in the wheel and through some simple calculations determine the distance travelled. As well as a non latching magnet (right) on the podcar to detect the magnet on the track and therefore determine our position on the track. There will be a total of five magnets on the track each representing a station.   
   <img src="https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/262/images/262_1_H.png?20200127094024" width="350" >
   <img src="https://cdn.shopify.com/s/files/1/1978/9859/products/03_25_1024x1024.jpg?v=1499266671" width="350" >
   

 



 

  
