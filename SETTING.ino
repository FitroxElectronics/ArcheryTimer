/* --------------------------------------------- Setting Program --------------------------------------------- */
void SET_PROG() {
  digitalWrite(DEVICE_INDICATOR, HIGH);
  // Stage = 0 set call time
  while (SETTING_STAGE == 0) {
    digitalWrite(RED_LIGHT, HIGH);
    digitalWrite(YELLOW_LIGHT, LOW);
    digitalWrite(GREEN_LIGHT, HIGH);
    MAIN_DISPLAY.setChar(0, 4, 'c', false);
    SET_CALLTIME();
  }

  // Stage = 1 set shooting time
  while (SETTING_STAGE == 1) {
    MAIN_DISPLAY.setChar(0, 4, 'l', false);
    SET_SHOOTINGTIME();
  }

  digitalWrite(DEVICE_INDICATOR, LOW);
}


/* -------------------------------------------- Call Time Setting -------------------------------------------- */
void SET_CALLTIME() {
  int DIGIT_2 = CALL_TIME / 100;
  int DIGIT_1 = (CALL_TIME % 100) / 10;
  int DIGIT_0 = (CALL_TIME % 100) % 10;

  // Set call time 0 - 100
  if (digitalRead(UP_BUTTON) == HIGH) {
    delay(20);
    CALL_TIME = CALL_TIME + 1;
    if (CALL_TIME > 100) {
      CALL_TIME = 0;
    }
    // Calculate digit to show on Display
    DIGIT_2 = CALL_TIME / 100;
    DIGIT_1 = (CALL_TIME % 100) / 10;
    DIGIT_0 = (CALL_TIME % 100) % 10;
  }
  if (digitalRead(DOWN_BUTTON) == HIGH) {
    delay(20);
    CALL_TIME = CALL_TIME - 1;
    if (CALL_TIME < 0) {
      CALL_TIME = 100;
    }
    // Calculate digit to show on Display
    DIGIT_2 = CALL_TIME / 100;
    DIGIT_1 = (CALL_TIME % 100) / 10;
    DIGIT_0 = (CALL_TIME % 100) % 10;
  }

  // Show on display
  MAIN_DISPLAY.setDigit(0, 0, DIGIT_0, false);
  MAIN_DISPLAY.setDigit(0, 1, DIGIT_1, false);
  MAIN_DISPLAY.setDigit(0, 3, DIGIT_2, false);

  // if press START, memory and go to next stage
  if (digitalRead(START_BUTTON) == HIGH) {
    delay(50);
    EEPROM.update(CALLTIME_ADDR, CALL_TIME);
    SETTING_STAGE = 1;
  }
  delay(200);
}


/* ------------------------------------------ Shooting Time Setting ------------------------------------------ */
void SET_SHOOTINGTIME() {
  int DIGIT_2 = SHOOTING_TIME / 100;
  int DIGIT_1 = (SHOOTING_TIME % 100) / 10;
  int DIGIT_0 = (SHOOTING_TIME % 100) % 10;

  // Set shooting time 0 - 600
  if (digitalRead(UP_BUTTON) == HIGH) {
    delay(20);
    SHOOTING_TIME = SHOOTING_TIME + 1;
    if (SHOOTING_TIME > 600) {
      SHOOTING_TIME = 0;
    }
    // Calculate digit to show on Display
    DIGIT_2 = SHOOTING_TIME / 100;
    DIGIT_1 = (SHOOTING_TIME % 100) / 10;
    DIGIT_0 = (SHOOTING_TIME % 100) % 10;
  }
  if (digitalRead(DOWN_BUTTON) == HIGH) {
    delay(20);
    SHOOTING_TIME = SHOOTING_TIME - 1;
    if (SHOOTING_TIME < 0) {
      SHOOTING_TIME = 600;
    }
    // Calculate digit to show on Display
    DIGIT_2 = SHOOTING_TIME / 100;
    DIGIT_1 = (SHOOTING_TIME % 100) / 10;
    DIGIT_0 = (SHOOTING_TIME % 100) % 10;
  }

  // Show on display
  MAIN_DISPLAY.setDigit(0, 0, DIGIT_0, false);
  MAIN_DISPLAY.setDigit(0, 1, DIGIT_1, false);
  MAIN_DISPLAY.setDigit(0, 3, DIGIT_2, false);

  // if press START, memory and go to next stage
  if (digitalRead(START_BUTTON) == HIGH) {
    delay(50);
    EEPROM.update(SHOOTINGTIME_ADDR, SHOOTING_TIME);
    SETTING_STAGE = 2;
  }
  delay(200);
}
