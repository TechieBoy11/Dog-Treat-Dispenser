// Author: Logan Johnson
// Date: 04/27/2026
// Version 1.0
#include <Servo.h>

// pin definition
#define BUZZER_PIN 9
#define SERVO_PIN 3

#define UP_BUTTON_PIN 12
#define DOWN_BUTTON_PIN 11
#define MODE_BUTTON_PIN 13

#define LED_PIN_A A4
#define LED_PIN_B A5
#define LED_PIN_DP 2
#define LED_PIN_C 4
#define LED_PIN_D 5
#define LED_PIN_E 6
#define LED_PIN_F 7
#define LED_PIN_G 8 

/////////// ADJUSTABLE VARIABLES///////////////////////////////////////////////////////
// servo positions 
const int drop = 0;                  // Position of the servo for drop command (low)
const int hold = 65;                 // Position of the servo for drop command (high)

const unsigned long waitTime = 0;    // time before drop is activated (ms)

///////////////////////////////////////////////////////////////////////////////////////

// loop variables
Servo myservo;                      // create servo object to control a servo
bool state = true;                  
bool changed = false;
int buttonState = 0;


void setup() {
  Serial.begin(9600);

  // Buttons
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);

  //LED display
  pinMode(LED_PIN_A, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  pinMode(LED_PIN_C, OUTPUT);
  pinMode(LED_PIN_D, OUTPUT);
  pinMode(LED_PIN_E, OUTPUT);
  pinMode(LED_PIN_F, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_DP, OUTPUT);

  // Others
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);   

}

// main control loop
void loop() {
  // button controls
  buttonState = digitalRead(MODE_BUTTON_PIN);
  if (buttonState == LOW){
    state = !state;
    changed = true;
  }
  

  // runs on state change
  if (changed) {
    dropTrigered();
    changed = false;
  }  

  // postion selection
  if (state)
    holdTreat();
  else 
    dropTreat();

}

// drop sequence
void dropTrigered() {
  aleart();

  for (int i=0; i < 3; i++){
    dropTreat();
    delay(1000);
    holdTreat();
    delay(1000);
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
  for (int i=0; i<3; i++) {
    tone(BUZZER_PIN, 1000, 750); // 1 kHz tone
    delay(500);
    tone(BUZZER_PIN, 750, 500); // 1 kHz tone
    delay(500);
    tone(BUZZER_PIN, 1250, 1000); // 1 kHz tone
    delay(2000);

  }
  
}


