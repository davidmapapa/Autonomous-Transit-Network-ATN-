# ATN Project using Lolin D32 microcontroller 
/*
 * Written by David Mapapa on Arduino IDE 
 * 
 * This code allow a pod car to run on the inner and outer section of a track. By switching the servo motor either left or                     
 * right. In order to avoid collisions the podcar retreives ultrasoincs, wheel encoder and marker count data to know 
 * where it is position and how far are the other pods.
 * The data are then send to the an IP address server that would take care of mapping all the podcars postions via a software
 * In addittion a webrowser page that can allow the user to switch the pod either left or right is created using 
 * ip address allocated to the ESP device by your local network
 */

#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "KeystoneWifi4";                 // WiFi name 
const char *password = "Melodybear3322LL";          // WiFi password
//const char* ssid = "ATTwvqYWQs";
//const char* password = "ds?37=qg545n";

// Host ip that received the data. Make sure to change it to your computer's ip 
// Also make sure to have a web server that can read the data sent 
  
  const char* host ="10.0.0.156";
//const char* host ="192.168.1.192";
//const char* host ="192.168.1.200";
//const char* host ="192.168.1.137";
//Bill's IP address = 192.168.1.137


WiFiClient client;            // Creating an object of the WiFiClient's class 
WiFiServer server(80);       // Creating an object of the WiFiServer's class 

#include <Adafruit_NeoPixel.h> 
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket neopixel
#endif
#define PIN        5 // Neopixel pin eopixel pin
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible countMarkerues.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYcountMarker 100 // Time (in milliseconds) to pause between pixels
String green;  
String red;               // string to match the colors requested 
String blue;
String yellow;
String maroon;
String cyan;
String white;
String magenta;

//ServoPin variables
int servoPin = 15; // Servo Pin 
// Pin 18 or Pin 14 depending on which board your are using
int servoPin2 = 18; // Servo Pin 
int pos = 5;  // variable to store the servo position
int pos2= 180; // variable to store the servo position2
int allowSwitch; 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// Ulrasonic sensor variables 
const int pingPinF04 = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPinF04 = 4 ; // Echo Pin of Ultrasonic Sensor
const int pingPinB12 = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPinB12 = 12 ; // Echo Pin of Ultrasonic Sensor
int  stopDistance = 20 ;
int  miDistance = 50;
int speeDistance = 90;
int sensitivity = 22; // for ultrasonic library 

// hall sensor variables 
const int encoderWheel = 16;     // For encoder wheel count
const int railMarker = 19;   // For Magnet rail count 
volatile long countMarker = 0;        // railMarker count
volatile long countStep = 0;
volatile long countStepLast = 0; 
volatile long timeElapsed = 0;
volatile long stepChange = 0;  
volatile long mmTraveled = 0 ;
// Wheel diameter = 25mm >> Wheel Circumference = (25)*pi = 78.54 mm
// There are 12 magnets in the wheel evenly spaced 
// 78.54 mm per 12 counts
// 6.55 mm per count or per magnet
float stepMM = 6.55; 
  
int skipMarker=0;

long int DELAYcountstrip = 80;
long int timeSpan = 50; // for rate of change of the wheel 
int markerDelay = 200; 
int printDelay = 200 ;
int neopixelDelay = 100;
long int loopMs = millis(); 
unsigned long previousMillis = millis(); 
long int neoPixelMs = loopMs + DELAYcountMarker ;
long int printMs = loopMs + printDelay;
long int counterMs = loopMs + markerDelay;
long int neopixelDelayMs = loopMs + neopixelDelay;
long int neoPixelstrip = loopMs + DELAYcountstrip;
const int watchdog = 10;        // Fréquence du watchdog - Watchdog frequency

// variable to store the random number generated for the switch function 
long randNumber;

//Motor variables
int motorSpeed = 90;
int motorMin = 40;
int motorMax = 110;
int motorNormal = 100;
int mmTorelance = 20;

String output26State = "in";
String output27State = "out";
String header;

void setup() {
  Serial.begin(115200); 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("begin set up");
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  //Servo set up 
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000); 
  myservo.attach(servoPin2, 1000, 2000); 

  // Analog out for drive motor
  // Base File in >> Examples >> ESP32 >> AnalogOut >> SigmaDelta 
  //setup channel 0 with frequency 312500 Hz
  sigmaDeltaSetup(0, 312500);
  //attach pin 25 to channel 0
  sigmaDeltaAttachPin(25,0);
  //attach pin 26 to channel 0
  sigmaDeltaAttachPin(26,0);
  //initialize channel 0 to off
  sigmaDeltaWrite(0, 0);

  // initialize the hall effect sensor pin as an input:
  pinMode(encoderWheel, INPUT_PULLUP);     
  attachInterrupt(digitalPinToInterrupt(encoderWheel), interruptMarker, CHANGE);

 // initialize the hall effect sensor pin as an input:
  pinMode(railMarker, INPUT_PULLUP);     
  attachInterrupt(digitalPinToInterrupt(railMarker), interruptWheel, CHANGE);
  server.begin();
 }


void loop() {
  
  // define the ultrasonic countSteps variables 
  long mmF;
  long mmB;

  long distanceMM = stepMM * countStep ;
  // 78.54 mm per 12 counts
  // 6.55 mm per count

  //Store ultrasonic countSteps from Front and Back ultrasonics 
  mmF = Ultra(pingPinF04,echoPinF04 );
  mmB = Ultra(pingPinB12,echoPinB12 ); 
  
  // Ignore printing for printDelay period 
  if (millis() > printMs) { 
    printMs = millis() + printDelay;
    Serial.print(mmF);
    Serial.print("mmF");
    Serial.print("  :  ");
    Serial.print(mmB);
    Serial.print("mmB  ");
    Serial.print("magnet_count: ");
    Serial.print(countMarker);
    Serial.print("  encoder_countStep: ");
    Serial.print(distanceMM);
    Serial.print(" mm ");
    Serial.print(" motorSpeed: ");
    Serial.print(motorSpeed);
    Serial.print(" mmTraveled");
    Serial.print(mmTraveled);
    Serial.print("  :  ");
    Serial.print(allowSwitch);
    Serial.println();
  }

  // normal front and back 
  if (mmB > speeDistance && mmF > miDistance) {
      speedNormal();
      Neocolor("green");
     }
  //Approaching barrier 
   else if (mmF <= miDistance && mmF > stopDistance) {
      midStop();
      Neocolor("yellow");
    }
  //Full stop 
   else if (mmF <= stopDistance) {
      fullStop();
      Neocolor("red");
    }
  //Speed up 
  else if (mmB <= speeDistance) {
      rearAccelerator();
      Neocolor("blue");
    }
  
  if (countMarker > 3) {
    countMarker =0;
    skipMarker = 0;
    }
  if (countMarker == 0) {
    if (distanceMM >=720 && distanceMM <=1000) {
       allowSwitch = 1;
      }
     else {
        allowSwitch = 0;
     }
  }

  // Make the switch at counter marker #1
  if (countMarker == 1 && skipMarker==0 &&  allowSwitch == 1 ) {
      randNumber = random(0, 2);
      if (randNumber == 0) {
          myservo.write(pos2);
        }
      else if (randNumber == 1) {
          myservo.write(pos);
        }
        skipMarker++;
    }

  unsigned long currentMillis = millis();
   if ( currentMillis - previousMillis > watchdog ) {
      previousMillis = currentMillis;
      WiFiClient client;
      
  if (client.connect(host, 8080)) {
    String url ="ajax_pod?pod=1&";
    url +=  sendData();
    client.print(String("GET ") +url + " HTTP/1.1\r\n" + "HOST: " +host+ "\r\n"+
    "Connection: close\r\n\r\n");
      unsigned long timeout = millis();
      while (client.available() == 0) {
        if (millis() - timeout > 10) {
          Serial.println(">>> Client Timeout !");
          client.stop();
          return;
        }
      }
      // Read all the lines of the reply from server and print them to Serial
      while(client.available()) {
        String serialStr = client.readStringUntil('\r');
        Serial.print(serialStr);
    }
   }
  }


 WiFiClient client1 = server.available(); 
 if (client1) {                             // If a new client connects,
   Serial.println("New Client.");          // print a message out in the serial port
   String currentLine = "";                // make a String to hold incoming data from the client
    while (client1.connected()) {            // loop while the client's connected
     if (client1.available()) {             // if there's bytes to read from the client,
       char c = client1.read();             // read a byte, then
       Serial.write(c);                    // print it out the serial monitor
       header += c;
        if (c == '\n') {                    // if the byte is a newline character
       // if the current line is blank, you got two newline characters in a row.
      // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client1.println("HTTP/1.1 200 OK");
            client1.println("Content-type:text/html");
            client1.println("Connection: close");
            client1.println();
            // turns the move car in or out
            if (header.indexOf("GET /inStation") >= 0) {
              myservo.write(pos2);
              Serial.println("rotate in");
            } else if (header.indexOf("GET /outStation") >= 0) {
              myservo.write(pos);
              Serial.println("rotate out");
            }
            // Display the HTML web page
            client1.println("<!DOCTYPE html><html>");
            client1.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client1.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the in/out buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client1.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client1.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client1.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client1.println(".button2 {background-color: #555555;}</style></head>");
            // Web Page Heading
            client1.println("<body><h1>Track Switches</h1>");
            // Display current state, and IN/OUT buttons   
            client1.println("<p>Inner track: " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State== "in") {
              client1.println("<p><a href=\"/inStation\"><button class=\"button\">RIGHT</button></a></p>");
            } 
            client1.println("<p>Outter track: " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="out") {
              client1.println("<p><a href=\"/outStation\"><button class=\"button\">LEFT</button></a></p>");
            } 
            client1.println("</body></html>");
            // The HTTP response ends with another blank line
            client1.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client1.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  } 
 } 
void speedNormal() {
  if( millis()  > timeElapsed) {
      timeElapsed = millis() + timeSpan;  // check speed very 100 ms
      stepChange = countStep - countStepLast ;
      countStepLast = countStep;
      mmTraveled =  stepChange * stepMM * 2 / timeSpan; 
      if(mmTraveled < motorNormal){
          motorSpeed = motorSpeed + 10;
        } 
      else if( mmTraveled + mmTorelance > motorNormal) {
             motorSpeed = motorSpeed - 20;
          } 
      }
      motorSpeed=constrain(motorSpeed,motorMin,motorMax); 
      sigmaDeltaWrite(0, motorSpeed);
  }

void fullStop() {
  motorSpeed = 0;
  sigmaDeltaWrite(0, motorSpeed);
}

void midStop(){
  if (millis() > neoPixelMs) {
    neoPixelMs = millis() + neopixelDelay;
    stepChange = countStep - countStepLast ;
    countStepLast = countStep;
    mmTraveled =  stepChange * stepMM * 2 / timeSpan;  
    if (mmTraveled>20) {
      motorSpeed=motorSpeed/1.01;
     }
    else if (mmTraveled<20) {
      motorSpeed++;
     }
  }
  motorSpeed=constrain(motorSpeed,10,40); 
  sigmaDeltaWrite(0, motorSpeed);
}

void rearAccelerator () {
  if (millis() > neoPixelMs) {
    neoPixelMs = millis() + 50;
    stepChange = countStep - countStepLast ;
    countStepLast = countStep;
    mmTraveled =  stepChange * stepMM * 2 / timeSpan;  
    if (mmTraveled<140) {
      motorSpeed++;
     }
  }
  motorSpeed=constrain(motorSpeed,110,140); 
  sigmaDeltaWrite(0, motorSpeed); 
}

void interruptMarker() {
      countMarker ++;
      countStep = 0;  // Set counterStep to zero at each increment of marker 
   }

void interruptWheel() {
    countStep ++ ;
   }

const int Ultra(const int Ping, const int Echo) { // returns disctance in mm
    long duration;
    pinMode(Ping, OUTPUT);  // send the ping
    digitalWrite(Ping, HIGH);  // start the ping
    delayMicroseconds(5);   // run for 5 microseconds
    digitalWrite(Ping, LOW);  // stop pinging
    pinMode(Echo, INPUT);  // switch to echo
    duration = pulseIn(Echo, HIGH);  // read the echo
    return microsecondsToMM(duration); 
 }

long microsecondsToMM(long microseconds) {
    return (microseconds / sensitivity / 2)* 10 ;
    // sensitivity changed from 29 to 26
  }

void Neocolor(String var)
{
  if (millis() > neoPixelMs) {
    neoPixelMs = millis() + DELAYcountMarker;
    pixels.clear(); // Set all pixel colors to 'off'
    // The first NeoPixel in a strand is #0, second is 1, all the way up
    // to the count of pixels minus one.
    for(int i=0; i<NUMPIXELS; i++) { 
      // For each pixel...
        if (var == "red") {
          // pixels.Color() takes RGB countMarkerues, from 0,0,0 up to 255,255,255
          // Here we're using a moderately bright red color:
          pixels.setPixelColor(i, pixels.Color(150, 0, 0));
        }
        else if (var == "green") { 
          // Here we're using a moderately bright green color:
          pixels.setPixelColor(i, pixels.Color(0, 150, 0));
        }
        else if (var == "blue") {
          // Here we're using a moderately bright blue color:
          pixels.setPixelColor(i, pixels.Color(0, 0, 150));
        }
        else if (var == "yellow") {
          // Here we're using a moderately bright yellow color:
          pixels.setPixelColor(i, pixels.Color(150, 150, 0));
        }
        else if (var == "maroon") {
          // Here we're using a moderately bright yellow color:
          pixels.setPixelColor(i, pixels.Color(128, 0, 0));
        }
        else if (var == "magenta") {
          // Here we're using a moderately bright yellow color:
          pixels.setPixelColor(i, pixels.Color(150, 0,150));
        }
        else if (var == "cyan") {
          // Here we're using a moderately bright yellow color:
          pixels.setPixelColor(i, pixels.Color(0, 150, 150));
        }
        else if (var == "white") {
          // Here we're using a moderately bright yellow color:
          pixels.setPixelColor(i, pixels.Color(150, 150, 150));
        }
        pixels.show();   // Send the updated pixel colors to the hardware.
     }
        delay(DELAYcountMarker); // Pause before next pass through loop
    }
}

String sendData() {
  // define the ultrasonic countSteps variables 
  long mmF;
  long mmB;
  long distanceMM = stepMM * countStep ;
  //Store ultrasonic countSteps from Front and Back ultrasonics 
  mmF = Ultra(pingPinF04,echoPinF04 );
  mmB = Ultra(pingPinB12,echoPinB12 ); 

  //String statusTemplate = "{\"fu\": DATA1,\"bu\": DATA2,\"cm\": DATA3,\"st\": DATA4}";
  //String statusTemplate = "fu=DATA1&bu=DATA2&cm=DATA3&st=DATA4";
  String statusTemplate = "fu="+String(mmF)+"&bu="+String(mmB)+"&cm="+String(countMarker)+"&st="+String(distanceMM) ;
  
  statusTemplate.replace("DATA1", String(mmF));
  statusTemplate.replace("DATA2", String(mmB));
  statusTemplate.replace("DATA3", String(countMarker));
  statusTemplate.replace("DATA4", String(distanceMM));
  
  return statusTemplate;
}

