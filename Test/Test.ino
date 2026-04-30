
#include <Servo.h>

// pin definition
#define BUZZER_PIN 9 
#define UP_BUTTON_PIN 12
#define DOWN_BUTTON_PIN 11
#define MODE_BUTTON_PIN 13
#define SERVO_PIN 3
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

void loop() {
  // Buttons test
  //Serial.println("Starting button tests");
  buttonTest(MODE_BUTTON_PIN);
  buttonTest(UP_BUTTON_PIN);
  buttonTest(DOWN_BUTTON_PIN);

  // Buzzer test
  Serial.println("Starting buzzer tests");
  //buzzerTest();

  // Servo test
  //Serial.println("Starting servo tests");
  //servoTest();

  //Display test
  Serial.println("Starting display tests");
  displayTest();
}

void buttonTest(int PIN) {
  Serial.println(PIN);
  int count = 0;
  while (true){
    buttonState = digitalRead(PIN);
    if (buttonState == LOW){
      Serial.println("Button worked");
      count++;
      delay(500);
    }

    if (count >= 3){
      Serial.print("Button Test passed: ");
      Serial.println(PIN);
      break;
    }
  }
}

void buzzerTest() {
    tone(BUZZER_PIN, 1000, 1000); // 1 kHz tone
    delay(500);
    tone(BUZZER_PIN, 750, 1000); // 1 kHz tone
    delay(500);
    tone(BUZZER_PIN, 1250, 1000); // 1 kHz tone
    delay(2000);
}

void servoTest() {
  myservo.write(hold);
  delay(2000);
  myservo.write(drop);
  delay(2000);
  myservo.write(hold);
  delay(2000);
  myservo.write(drop);
  delay(2000);
  myservo.write(hold);
  delay(2000);
  myservo.write(drop);
  delay(2000);
}

void displayTest() {
  digitalWrite(LED_PIN_A, LOW);
  digitalWrite(LED_PIN_B, LOW);
  digitalWrite(LED_PIN_C, LOW);
  digitalWrite(LED_PIN_D, LOW);
  digitalWrite(LED_PIN_E, LOW);
  digitalWrite(LED_PIN_F, LOW);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_DP, LOW);





  // A
  digitalWrite(LED_PIN_A, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_A, LOW);

  // B
  digitalWrite(LED_PIN_B, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_B, LOW);

  // C
  digitalWrite(LED_PIN_C, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_C, LOW);

  // D
  digitalWrite(LED_PIN_D, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_D, LOW);

  // E
  digitalWrite(LED_PIN_E, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_E, LOW);

  // F
  digitalWrite(LED_PIN_F, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_F, LOW);

  // G
  digitalWrite(LED_PIN_G, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_G, LOW);

  // DP
  digitalWrite(LED_PIN_DP, HIGH);
  delay(1500);
  digitalWrite(LED_PIN_DP, LOW);
}









