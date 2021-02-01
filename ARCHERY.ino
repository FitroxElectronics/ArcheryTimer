/**************************************************************************************************************
 *                                                ARCHERY TIMER                                               *
 *  SOFTWARE VERSION 1.0                                                                                      *
 *  RELEASE : JANUARY 2021                                                                                    *
 *                                                                                                            *
 *  DEVELOP BY FITROX ELECTRONICS :: CHIANG MAI, THAILAND                                                     *
 *  PROGRAMMER                                                                                                *
 *   - P. BANGTAWEE                                                                                           *
 **************************************************************************************************************/

/* ----------------------------------------- Include Library & Other ---------------------------------------- */
#include <EEPROM.h>
#include <LedControl.h>

/* -------------------------------------------- I/O Configulation -------------------------------------------- */
#define BATTERY_VOLTAGE A0                      // *INPUT - Read battery voltage
#define START_BUTTON A1                         // INPUT - START button
#define UP_BUTTON A2                            // INPUT - UP button
#define DOWN_BUTTON A3                          // INPUT - DOWN button
// A4 & A5 using as IIC communication
// 0 & 1 Reserve as UART Serial communication
#define MAX_CLOCK 2                             // OUTPUT - MAX7219 CLOCK pin
#define MAX_LOAD 3                              // OUTPUT - MAX7219 LOAD pin
#define MAX_DIN 4                               // OUTPUT - MAX7219 DIN pin
#define BUZZER 5                                // OUTPUT - Built-in buzzer
#define HORN 6                                  // OUTPUT - External horn
#define RED_LIGHT 7                             // OUTPUT - Red light indicator built-in & external
#define YELLOW_LIGHT 8                          // OUTPUT - Yellow light indicator built-in & external
#define GREEN_LIGHT 9                           // OUTPUT - Green light indicator built-in & external
#define AB_LIGHT 10                             // OUTPUT - AB light indicator built-in & external
#define CD_LIGHT 11                             // OUTPUT - CD light indicator built-in & external
#define BATTERY_INDICATOR 12                    // *OUTPUT - Battery indicator light
#define DEVICE_INDICATOR 13                     // *OUTPUT - Device indicator light

/* ---------------------------------------------- EEPROM Address --------------------------------------------- */
#define CALLTIME_ADDR 10
#define SHOOTINGTIME_ADDR 12

/* ------------------------------------------ Device Configulation ------------------------------------------- */
// MAX7219 drive 4-digit 7-segment Main display
#define MAX_NO 1                                // Use 1 MAX7219
LedControl MAIN_DISPLAY = LedControl(MAX_DIN, MAX_CLOCK, MAX_LOAD, MAX_NO);

/* ---------------------------------------------- Program Stage ---------------------------------------------- */
bool RUN_STAGE = false;                         // Stage to start/pause/resume program
bool AB_STAGE = true;                           // Stage to switch AB or CD
int PROG_MODE = 0;                              // *Program working mode
int PROG_STAGE = 0;                             // Program stage : Ready=0, Precount=1, Count=2
bool COLON = true;
bool PAUSE_PROG = false;
int SETTING_STAGE = 0;

/* -------------------------------------------- Program Variable --------------------------------------------- */
int CALL_TIME;                                  // Call time - settable
int SHOOTING_TIME;                              // Shooting time - settable
int ADVICE_TIME = 40;                           // *Advice time - settable

/* ---------------------------------------------- Time Variable ---------------------------------------------- */
unsigned long CURRENT_TIME;                     // Check current time
const unsigned long MINUTE_TIME = 60000;        // Minute
const unsigned long SECOND_TIME = 1000;         // Second
const unsigned long HALF_SECOND = 500;          // Half second
int HALF_COUNT = 0;
unsigned long LAST_BLINK;

/* -------------------------------------------- Button Condition --------------------------------------------- */
const unsigned long DEBOUNCE_PRESS = 100;       // Debounce time for press button
unsigned long LAST_DEBOUNCE;
const unsigned long LONG_PRESS = 2000;          // Long press button time
int START_BUTTON_STAGE = LOW;                   // START button stage
unsigned long START_CURRENT;                    // Check current stage for START button
unsigned long START_RELEASE;                    // Check when release START button

/* ----------------------------------------------- Setup Loop ------------------------------------------------ */
void setup() {
  // Initialization devices
  Serial.begin(9600);
  MAIN_DISPLAY.shutdown(0, false);
  MAIN_DISPLAY.setIntensity(0, 8);

  // INPUT pins
  pinMode(START_BUTTON, INPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);

  // OUTPUT pins
  pinMode(BUZZER, OUTPUT);
  pinMode(HORN, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(AB_LIGHT, OUTPUT);
  pinMode(CD_LIGHT, OUTPUT);
  pinMode(BATTERY_INDICATOR, OUTPUT);
  pinMode(DEVICE_INDICATOR, OUTPUT);

  // Set all OUTPUT 'OFF'
  digitalWrite(BUZZER, LOW);
  digitalWrite(HORN, LOW);
  digitalWrite(RED_LIGHT, LOW);
  digitalWrite(YELLOW_LIGHT, LOW);
  digitalWrite(GREEN_LIGHT, LOW);
  digitalWrite(AB_LIGHT, LOW);
  digitalWrite(CD_LIGHT, LOW);
  digitalWrite(BATTERY_INDICATOR, LOW);
  digitalWrite(DEVICE_INDICATOR, LOW);

  CALL_TIME = EEPROM.read(CALLTIME_ADDR);
  SHOOTING_TIME = EEPROM.read(SHOOTINGTIME_ADDR);
  SET_PROG();
  
}         // End setup

/* ------------------------------------------------ Main Loop ------------------------------------------------ */
void loop() {
  digitalWrite(RED_LIGHT, HIGH);
  digitalWrite(YELLOW_LIGHT, LOW);
  digitalWrite(GREEN_LIGHT, LOW);


  if (digitalRead(START_BUTTON) == HIGH) {
    delay(50);
    RUN_STAGE = true;
  }


  if (RUN_STAGE == false) {
  MAIN_DISPLAY.setChar(0, 0, '-', false);
  MAIN_DISPLAY.setChar(0, 1, '-', false);
  MAIN_DISPLAY.setChar(0, 3, '-', false);
  MAIN_DISPLAY.setChar(0, 4, '-', false);
  }


  if (RUN_STAGE == true) {
    
    LAST_BLINK = millis();
    // Buzzer 2 time & YELLOW Light to CALL signal
    BUZZER_HORN(2, 0);
    digitalWrite(RED_LIGHT, LOW);
    digitalWrite(YELLOW_LIGHT, HIGH);
    // Start CALL TIME program
    CALL_TIMER(CALL_TIME);

    // Set HALF_COUNT = 0 and start SHOOTING TIME program
    HALF_COUNT = 0;
    SHOOTING_TIMER(SHOOTING_TIME);
    
  }         // End if(RUN_STAGE == true)

}         // End main loop
