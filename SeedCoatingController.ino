#include "arduino_secrets.h"
/*
  Open Source Seed Coating Machine Controller
  by Lot Amoros
  Dronecoria
  https://dronecoria.org
  License
  GPLv3

  Arduino IoT Cloud Thing "SeedCoatingController"
  https://create.arduino.cc/cloud/things/6a11e07e-a0df-4612-b8d6-41e3dc5c0c59

  Arduino IoT Cloud Variables description
  int numberRepetitions;
  int msClose;
  float mlmsRelation;
  int msOpen;
  Thing and added at the end of this sketch.
*/

#include "thingProperties.h"


// constants used here to set pin numbers:
const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;     // the number of the pushbutton pin
const int buttonPin3 = 4;     // the number of the pushbutton pin

const int RelayPin1 =  7;      // enchufe
const int RelayPin2 =  8;      // the number of the LED pin
const int RelayPin3 =  9;      // the number of the LED pin
const int RelayPin4 =  10;      // the number of the LED pin
const int RelayPin5 =  11;      // the number of the LED pin
const int RelayPin6 =  12;      // the number of the LED pin

// state of the buttons:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status

int intMsOpen  = 100;
int intMsClose = 100;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  // initialize the LED pin as an output:
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void loop() {
  ArduinoCloud.update();

  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  
  //cycle();

  // check if the pushbutton is pressed. 
  if (buttonState1 == LOW) {
    // turn LED on:
    digitalWrite(RelayPin1, HIGH);
    digitalWrite(RelayPin2, HIGH);
  } else {
    // turn LED off:
    digitalWrite(RelayPin1, LOW);
    digitalWrite(RelayPin2, LOW);
  }

  if (buttonState2 == LOW) {
    // turn LED on:
    //digitalWrite(RelayPin5, HIGH);
    //digitalWrite(RelayPin6, HIGH);
    startCycle();
  } else {
    // turn LED off:
    //digitalWrite(RelayPin1, LOW);
    //digitalWrite(RelayPin2, LOW);
  }

 if (buttonState3 == LOW) {
    // turn LED on:
    digitalWrite(RelayPin3, HIGH);
    digitalWrite(RelayPin4, HIGH);
  } else {
    // turn LED off:
    digitalWrite(RelayPin3, LOW);
    digitalWrite(RelayPin4, LOW);
  }
}

/*void cycle(){
   time_now = millis();
    while(millis() < time_now + period){
        //wait approx. [period] ms
}*/

boolean cycle = false;
void startCycle() {
  
  if (!cycle){
    
  cycle = true;
  int msStart = millis();
  int time_now;

  for (int i = 0; i < numberRepetitions; i++)
  {
    digitalWrite(RelayPin1, HIGH);
    digitalWrite(RelayPin2, HIGH);
    //delay(100);
    //delay(intMsOpen);
    time_now = millis();
    while(millis() < time_now + intMsOpen){
    }
    digitalWrite(RelayPin1, LOW);
    digitalWrite(RelayPin2, LOW);
    //delay(intMsClose);
    time_now = millis();
    while(millis() < time_now + intMsClose){
    }
   
    //delay(100);
  }
  cycle = false;
  }
}

void onMlxmsChange() {
  // Do something
}

void onNumberRepetitionsChange() {
  // Do something
}

void onMsOpenChange() {
  // Do something
  intMsOpen = (int) msOpen;
}



void onMsCloseChange() {
  // Do something
    intMsClose = (int) msClose;
}


void onMlmsRelationChange() {
  // Do something
}



