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

const int digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

const int segmentPins[7] = {
  LED_PIN_A,
  LED_PIN_B,
  LED_PIN_C,
  LED_PIN_D,
  LED_PIN_E,
  LED_PIN_F,
  LED_PIN_G
};

/////////// ADJUSTABLE VARIABLES///////////////////////////////////////////////////////
// servo positions 
const int drop = 0;                  // Position of the servo for drop command (low)
const int hold = 65;                 // Position of the servo for drop command (high)

const int defaultTime = 4;                   // time before drop is activated (seconds)
int waitTime = 4;
int warningNum = 2;

///////////////////////////////////////////////////////////////////////////////////////

// loop variables
Servo myservo;                      // create servo object to control a servo
bool state = true;                  
bool changed = false;

int start = 1;
int up = 1;
int down = 1;



void setup() {
  Serial.begin(9600);

  // Buttons
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);

  //LED display
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(LED_PIN_DP, OUTPUT);

  // Others
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);   

}

// main control loop
void loop() {
  // button controls
  holdTreat();
  start = digitalRead(MODE_BUTTON_PIN);
  up = digitalRead(UP_BUTTON_PIN);
  down = digitalRead(DOWN_BUTTON_PIN);

  if (start == LOW){
    setNoise();
    delay(waitTime*10000);
    dropTrigered();
    waitTime = defaultTime;
    delay(6000);
  } else if (up == LOW && waitTime <9 ) {
    waitTime++;
    delay(250);
  } else if (down == LOW && waitTime > 1 ){
    waitTime--;
    delay(250);
  }

  displayDigit(waitTime);
  


/*
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
*/
}

void setTime() {

}



/////helper functions///////////////////////
// drop sequence
void dropTrigered() {
  aleart();

  for (int i=0; i < warningNum; i++){
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
  for (int i=0; i<warningNum; i++) {
    tone(BUZZER_PIN, 1500, 1000); // 1 kHz tone
    delay(250);
    displayDigit(waitTime);
    delay(250);
    clearDisplay();
    tone(BUZZER_PIN, 1000, 1000); // 1 kHz tone
    delay(250);
    displayDigit(waitTime);
    delay(250);
    clearDisplay();
    tone(BUZZER_PIN, 2000, 1000); // 1 kHz tone
    delay(500);
    displayDigit(waitTime);
    delay(500);
    clearDisplay();

  }
}

void setNoise () {
  tone(BUZZER_PIN, 500, 1000); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 750, 1000); // 1 kHz tone
  delay(500);
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}

void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
}


