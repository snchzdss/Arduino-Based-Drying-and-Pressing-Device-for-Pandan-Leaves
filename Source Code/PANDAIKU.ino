// Include necessary libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <Keypad.h>

// RELAY 
#define RELAY_ON LOW
#define RELAY_OFF HIGH

#define MOVE_FWD 5
#define MOVE_BWD 4
#define HEATER 6
#define FAN 7
#define BUZZER 8
#define LMS_FWD 3
#define LMS_BWD 2

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {37, 35, 33, 31}; //CHANGE PIN  37, 35, 33, 31
byte colPins[COLS] = {29, 27, 25, 23};  //CHANGE PIN 29, 27, 25, 23
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables for user input
int pressingTime = 0;

// Function Prototypes
// void setupProcess();
// void mainProcess();
// void countdownTimer(int seconds, const char* phase);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(MOVE_FWD, OUTPUT); digitalWrite(MOVE_FWD, RELAY_OFF);
  pinMode(MOVE_BWD, OUTPUT); digitalWrite(MOVE_BWD, RELAY_OFF);
  pinMode(BUZZER, OUTPUT); digitalWrite(BUZZER, RELAY_ON);
  pinMode(HEATER, OUTPUT); digitalWrite(HEATER, RELAY_ON);
  pinMode(FAN, OUTPUT); digitalWrite(FAN, RELAY_OFF);

  pinMode(LMS_FWD, INPUT_PULLUP);
  pinMode(LMS_BWD, INPUT_PULLUP);

  Serial.println("===READY===");
  displayMenu();
}

void loop() {
  serialCommand();
  // Serial.print(digitalRead(LMS_FWD));
  // Serial.print("||");
  // Serial.println(digitalRead(LMS_BWD));
  // delay(500);
}