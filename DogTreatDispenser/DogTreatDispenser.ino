// Author: Logan Johnson
// Date: 04/27/2026
// Version 1.0

#include <Servo.h>

// pin definition
#define BUZZER_PIN D0 
#define BUTTON_PIN 2
#define SERVO_PIN 9
#define LED TODO

/////////// ADJUSTABLE VARIABLES///////////////////////////////////////////////////////
// servo positions 
const int drop = 0;                  // Position of the servo for drop command (low)
const int hold = 65;                 // Position of the servo for drop command (high)

const unsigned long waitTime = 0    // time before drop is activated (ms)

///////////////////////////////////////////////////////////////////////////////////////

// loop variables
Servo myservo;                      // create servo object to control a servo
bool state = true;                  
bool changed = false;
int buttonState = 0;

// Program setup
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);                 
}

// main control loop
void loop() {
  // button controls
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH){
    state = !state;
    changed = true;
  }

  // postion selection
  if (state)
    holdTreat();
  else 
    dropTreat();

  // runs on state change
  if (changed) {
    aleart();
    delay(2000);
    changed = false;
  }    

}

// sets drop postion
void dropTreat(){
  myservo.write(drop);
  Serial.println("dropping");
}

// sets hold postion
void holdTreat() {
  myservo.write(hold);
  Serial.println("Holding");
}

// plays noise through buzzer
void aleart() {
  tone(BUZZER_PIN, 1000, 1000); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 750, 1000); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 1250, 1000); // 1 kHz tone
  delay(500);
}


