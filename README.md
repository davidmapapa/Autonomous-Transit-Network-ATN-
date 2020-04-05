# ABSTRACT
 As a proof of concept of an Autonomous Transit Network **(ATN)**, the Spartan Superway and Jpods car have designed a small scale model, that would display two or more cars autonomously running around a track while avoiding collision. Each vehicle (podcar) would follow its own route and in the instance of two vehicle coming in proximity of each other, the model would slow down one podcar and acclerate the other to avoid collision. This is done to imitate the Personal Rapid Transit **(PRT)** design, which would allow people to commute on vehicles located on elevated guideways or rails, avoiding traffic, buildings and natural habitats. Here are perfect illustrations of such system by the [click for CGTN News report](https://www.youtube.com/watch?v=QBp7HuzCCWU) and [click Jpod's video](https://www.youtube.com/watch?v=rRIzvfW8XXs).
 In this project, I will describe and list the necessary ressources needed in order to design, build and program a small scale podcar model. After going through this tutorial you should be able to grasp the necessary code in order to program a single pod. [click for single pod video](https://player.vimeo.com/video/390130443) and once you obtain the necessary software skills you can add multiple pods and build your own system. [click for two pods video](https://www.youtube.com/watch?v=rCR6fW-CSME).
The 3D print drawings and CAD necessary to build both the track and the vehicle can be found at www.jpods.com
Here will be listed the different electronics parts and the Arduino files necessary to program the pods. 
 
# TABLE OF CONTENTS 
##### 1.- [PCB and Microcontroller](###1.PCB%and%Microcontroller:) 
##### 2.Sensors
###### a.Description
###### b.Code 
##### 3. Conclusion <br /><br /><br /><br />  

 
 
 ## 1.PCB and Microcontroller: 
 __Printer Circuit Board__: 
The Printed Circuit Board (PCB) used in the podcar was specifically design by Jpods for this project. The board was design to fit an ESP LOLIN D32 board, a RASPBERRY PI, and multiple sensors. The board's link can be found by clicking below: [Board](https://drive.google.com/drive/u/0/folders/1CtqrttBD3XoiUPqs3ZEBOA0wLDOCQpJk). 
 Once the board received, I soldered the different connectors (2 pins, 3 pins and 4 pins), resistors, capacitors, OPamp and the LOLIN D32 connectors. A video of me assembling the board from scratch will be linked afterwards. 
 
__Microcontroller__:
The Lolin D32 is a chip that is part of the WEMOS ESP32 microcontroller family. The chip is compatible with the Arduino IDE as well as micropython. A major benefit of the chip is that it easily allows WiFi connection.

Here are pictures of an empty board, pins conncetors, resistors and capacitors before and after soldering. 
<img src="https://user-images.githubusercontent.com/58591461/74691817-32a8f080-5199-11ea-8c66-da995081eb52.jpg" width="350">
<img src="https://user-images.githubusercontent.com/58591461/74690625-95e45400-5194-11ea-99a9-ad1611ff258d.JPG" width="400">


Each board was placed in a single podcar.  
<img src="https://user-images.githubusercontent.com/58591461/74691691-a696c900-5198-11ea-8146-19ac58ae621d.jpg" width="390">  <img src="https://user-images.githubusercontent.com/58591461/74691734-d34ae080-5198-11ea-8845-0f1f017e3e73.jpg" width="400">

<br /><br /><br /><br />



## 2.Sensors: 
 In order to make a single pod operate autonomoulsy, different physical factors needed to be processed. This was done to ensure the safety and robustness of the system. Among those factors were the speed of the podcar vehicle, the front and back distances that seperating the vehicles from each other, the distance travelled by each vehicle, the station of each pod vehicle (inner or outter station) and finally the position of other podcar vehicles. 
To do so, we used few sensors that measured those aformentioned variables:  
   #### a. Neopixel: 
   ##### Description:
   Those are the string of LED located in the front of each vehicle with the purpose of reporting the status of the vehilce. The neopixel string will flash **Green** if there's no obstacle, **Red** if there's an obstacle in front of the vehicle and **Blue** there are any obstacle behind the vehicle. This is done by directly utilizing the distance reported by each ultrasonic sensors (Front and Back).
   
   <img src="https://cdn.sparkfun.com//assets/parts/9/3/7/2/12661-01a.jpg" width="250"> <img src="https://cdn.sparkfun.com//assets/parts/9/3/7/2/12661-03a.jpg" width="250">
   
   ##### Code:  
```C++
// Your code here
include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels
String green;
String red;
String blue;

void setup() {
  Serial.begin(115200);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop(){
  Serial.println("displaying red color");
  delay(500);
  Neocolor("red");
  Serial.println("displaying green color");
  delay(500);
  Neocolor("green");
  Serial.println("displaying blue color");
  delay(500);
  Neocolor("blue");
 }

void Neocolor(String var){
    pixels.clear(); // Set all pixel colors to 'off'
    // The first NeoPixel in a strand is #0, second is 1, all the way up
    // to the count of pixels minus one.
    for(int i=0; i<NUMPIXELS; i++)  { // For each pixel...
      if (var == "red")  {
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright red color:
        pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      }
      else if (var == "green") { 
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      }
      else if (var == "blue"){
        // Here we're using a moderately bright blue color:
        pixels.setPixelColor(i, pixels.Color(0, 0, 150));
      }
      pixels.show();   // Send the updated pixel colors to the hardware.
      delay(DELAYVAL); // Pause before next pass through loop
    }
}

```
<br /><br /><br />
   
   #### b. Ultrasonic sensors:
   ##### Description:
   An ultrasonic sensor can be considered as an electronic device that measure the distance between an object and the sensor itself using ultrasonic waves. The ultrasonic sensor sends a wave signal through a Ping signal and accounts for the time it takes for the wave to hit an object and bounce back. Knowing the speed at which an ultrasonic wave travel, it easy to determine the distance at which the object is located. The ultrasonic sensors are located in the front and back of the vehicle scaning if there are any other vehicle in proximty.  
   
   <img src="https://images-na.ssl-images-amazon.com/images/I/71-TKtOybqL._SL1500_.jpg" width="305">
 
 ##### Code:
 ```C++
// Your code here
const int pingPinF04 = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPinF04 = 4 ; // Echo Pin of Ultrasonic Sensor

const int pingPinB12 = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPinB12 = 12 ; // Echo Pin of Ultrasonic Sensor

void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); // Starting Serial Terminal

}

void loop() {
  long durationF, inchesF, cmF;
  long durationB, inchesB, cmB;
// Do the front
  pinMode(pingPinF04, OUTPUT);  // send the ping
  digitalWrite(pingPinF04, HIGH);  // start the ping
  delayMicroseconds(5);   // run for 5 microseconds
  digitalWrite(pingPinF04, LOW);  // stop pinging
  pinMode(echoPinF04, INPUT);  // switch to echo
durationF = pulseIn(echoPinF04, HIGH);  // read the echo
 
// Do the back
  pinMode(pingPinB12, OUTPUT);
  digitalWrite(pingPinB12, HIGH);
  delayMicroseconds(5);   // run for 5 microseconds
  digitalWrite(pingPinB12, LOW);  // stop pinging
  pinMode(pingPinB12, INPUT);  // switch to echo
  durationB = pulseIn(echoPinB12, HIGH);  // read the echo

inchesF = microsecondsToInches(durationF);
inchesB = microsecondsToInches(durationB);

cmF = microsecondsToCentimeters(durationF);
cmB = microsecondsToCentimeters(durationB);

Serial.print(cmF);
Serial.print("cmF");
Serial.print("  :  ");
Serial.print(cmB);
Serial.print("cmb");
Serial.println();
  delay(20);
}

long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

```
<br /><br /><br />
 


    
   #### c. DC Motor: 
   ##### Description:
   A DC Motor is an actuator device that converts electric current into mechanical energy. That energy is represented in terms of speed. In this project the DC motor are the main component responsible for the motion of the vehicle. The motors run on a track at constant speed and accelerate when there's an obstacle coming from the back and decelerate if the ultrasonic sensor detects an obstacle in the front.  
   
   <img src="https://www.wiltronics.com.au/wp-content/uploads/images/make-and-create/gear-motor-dc-toy-car-wheel-arduino.jpg" width="305">
 
 ##### Code:
  ```C++
// Your code here

   void setup(){
    //setup channel 0 with frequency 312500 Hz
    sigmaDeltaSetup(0, 312500);
    //attach pin 18 to channel 0
    sigmaDeltaAttachPin(18,0);
    //initialize channel 0 to off
    sigmaDeltaWrite(0, 0);
}

void loop(){
    //slowly ramp-up the value
    //will overflow at 256
    static uint8_t i = 0;
    sigmaDeltaWrite(0, i++);
    delay(100);
}


```
<br /><br /><br />     
   #### d. Servo Motor:
   ##### Description:
   A servo motor is also an actuator device, that can precisely determine its linear and angular position, velocity and acceleration. A servo motor has a build in closed-loop system that determines its postion using position feedback control. In our project the servo motors are used to switch the podcar from the inner to the outer track.  
   
   <img src="https://media.digikey.com/Photos/DFRobot/MFG_SER0006.jpg" width="305" >
   
   ##### Code:
   ```C++
// Your code here

#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 5;
int pos2= 40;// variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 15;
int servoPin2 =14;

void setup() {
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
	myservo.attach(servoPin2, 1000, 2000);
	 // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
}

void loop() {

	//for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		
		delay(1500);             // waits 15ms for the servo to reach the position
	//}
	//for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		myservo.write(pos2);    // tell servo to go to position in variable 'pos'
		delay(1500);             // waits 15ms for the servo to reach the position
	//}
}


```
<br /><br /><br />
   
   #### e. Hall Effect:
   ##### Description:
   An Hall effect sensor is a device that is able to detect a magnetic field. Therefore, one can use an hall sensor to detect magnets that are located at close proximity. We will use two different type of hall sensor, a latching sensor (up) that would detect small magnets placed in the wheel and through some simple calculations determine the distance travelled by the podcar. As well as a non latching sensor (down), on the podcar to detect the magnets palced on the track as a representation of stations. There will be a total of five magnets on the track each of them will help determine the relative postion of a podcar as it passes through it.  
   
   
   <img src="https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/262/images/262_1_H.png?20200127094024" width="305" >
   <img src="https://cdn.shopify.com/s/files/1/1978/9859/products/03_25_1024x1024.jpg?v=1499266671" width="305" >
   
 
 ##### Code:
  ```C++
//
 const int hallPin = 16;     // the number of the hall effect sensor pin
volatile byte val = 0;


void setup() {
  Serial.begin(115200);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
        
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT_PULLUP);     

attachInterrupt(digitalPinToInterrupt(hallPin), interruptHall, CHANGE);
}

void loop() {
  Serial.println(val);
  delay(1000);
}

void interruptHall() {
    val ++ ; 
   }
   
``` 

<br /><br /><br />
## 3. Conclusion
The project is small scale proof of concept of a Personal Rapid Transit system. The project mostly highlights and explains the various sensors and code required to understand the scale_model code file upload at the top of the page. Once the code downloaded, one can easily implement it multiple podcars and build a system of their own.    
   
  

 



 

  
