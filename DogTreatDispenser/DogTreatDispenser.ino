// Author: Logan Johnson
// Date: 04/27/2026
// Version 3.2
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

/////////// //////////////////ADJUSTABLE VARIABLES////////////////////////////////////
// servo positions 
const int drop = 0;                  // Position of the servo for drop command (low)
const int hold = 65;                 // Position of the servo for drop command (high)

// Time
const bool isHours = true;           // true for hour mode false for minuts
const int defaultTime = 8;           // default starting time
int waitTime = defaultTime;
const int warningNum = 4;            // Number of warnings before drop        
const int buttonDelay = 500;         // Input lag for buttons

// Tones marking time passed
const bool hourlyTone = true;        // beep every hour
const bool quarterlyTone = false;    // beep every 15 min

///////////////////////////////////////////////////////////////////////////////////////

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

// loop variables
Servo myservo;                      // create servo object to control a servo

int start = 1;
int up = 1;
int down = 1;

int quarter = 0;
bool flash = false;
bool holding = false;



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
  startNoise(); 
}

// main control loop
void loop() {
  
  if (!holding){
    holdTreat();
    holding = true;
  }

  // button controls
  start = digitalRead(MODE_BUTTON_PIN);
  up = digitalRead(UP_BUTTON_PIN);
  down = digitalRead(DOWN_BUTTON_PIN);

  // Start timer and drop sequence
  if (start == LOW){
    setNoise();
    if (isHours)
      delayHandleHour(waitTime);
    else
      delayHandleMin(waitTime);
    dropTriggered();
    waitTime = defaultTime;
    quarter = 0;
    holding = false;
    delay(3000);

  // increase time
  } else if (up == LOW) {
    delay(50);
    down = digitalRead(DOWN_BUTTON_PIN);

    if (down == LOW){
      if (quarter >= 3)
        quarter = 0;
      else
        quarter++;
    } else if (waitTime < 9)
      waitTime++;
    delay(buttonDelay);

  // decrease time
  } else if (down == LOW){
    delay(50);
    up = digitalRead(UP_BUTTON_PIN);

    if (up == LOW){
      if (quarter >= 3)
        quarter = 0;
      else
        quarter++;
    } else if (waitTime > 1)
      waitTime--;
    delay(buttonDelay);

  } else{
    delay(buttonDelay);
  }

  displayControl(waitTime, flash);
  flash = !flash;
}

/////helper functions///////////////////////
void test() {
  holdTreat();
  start = digitalRead(MODE_BUTTON_PIN);

  // runs on state change
  if (start) {
    delay(3000);
    dropTriggered();
    delay(3000);
  }  

}

// drop sequence
void dropTriggered() {
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
  tone(BUZZER_PIN, 3000, 500); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 3000, 500); // 1 kHz tone
  delay(500);
}

void setNoise () {
  tone(BUZZER_PIN, 500, 1000); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 750, 1000); // 1 kHz tone
  delay(500);
}

void startNoise() {
  tone(BUZZER_PIN, 250, 500); // 1 kHz tone
  delay(500);
  tone(BUZZER_PIN, 500, 500); // 1 kHz tone
  delay(500);
}

// Display functions
void displayDelay(unsigned long waitTime, int displayTime) {
  unsigned long startTime = millis();
  unsigned long lastFlash = millis();
  bool dFlash = false; 
  while (millis() - startTime < waitTime) {
      // Toggle flash every 500 ms
      if (millis() - lastFlash >= 500) {
          dFlash = !dFlash;
          lastFlash += 500;
      }
      displayControl(displayTime, dFlash);
      delay(1);
  }
}

void displayControl(int time, bool blink){
  // display
  if (quarter == 1 || quarter == 3) {
    if (blink) 
      displayDigit(time);
    else
      clearDisplay();
  } else {
    displayDigit(time);
  }

  if (quarter == 3)
    digitalWrite(LED_PIN_DP, 1);
  else 
    digitalWrite(LED_PIN_DP, 0);
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }

  if (quarter == 2 || quarter == 3)
    digitalWrite(LED_PIN_DP, 1);
  else
    digitalWrite(LED_PIN_DP, 0);
}

void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
  digitalWrite(LED_PIN_DP, LOW);
}

// delay functions
void delayHandleMin(int time) {
  int totalQuarters = time * 4 + quarter;
  while (totalQuarters > 0) {
      int displayTime = totalQuarters / 4;
      displayDelay(60000UL, displayTime);
      totalQuarters--;
      quarter = totalQuarters % 4;
      
      if (hourlyTone && quarter == 0)
        tone(BUZZER_PIN, 250, 500);
      else if (quarterlyTone)
        tone(BUZZER_PIN, 250, 500);
  }
}

void delayHandleHour(int time) {
    int totalQuarters = time * 4 + quarter;
    while (totalQuarters > 0) {
        int displayTime = totalQuarters / 4;
        displayDelay(900000UL, displayTime);
        totalQuarters--;
        quarter = totalQuarters % 4;

        if (hourlyTone && quarter == 0)
          tone(BUZZER_PIN, 250, 500);
        else if (quarterlyTone)
          tone(BUZZER_PIN, 250, 500);
    }
}
