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
