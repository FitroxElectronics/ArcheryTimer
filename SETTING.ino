/* --------------------------------------------- Setting Program --------------------------------------------- */
void SET_PROG(){
  digitalWrite(DEVICE_INDICATOR, HIGH);
  // Stage = 0 set call time
  while(SETTING_STAGE == 0){
    digitalWrite(RED_LIGHT, LOW);
    digitalWrite(YELLOW_LIGHT, HIGH);
    digitalWrite(GREEN_LIGHT, LOW);
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Setting");
    LCD.setCursor(0, 1);
    LCD.print("CALL Time ");
    SET_CALLTIME();
  }

  // Stage = 1 set shooting time
  while(SETTING_STAGE == 1){
    LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Setting");
  LCD.setCursor(0, 1);
  LCD.print("SHOOTING Time ");
  SET_SHOOTINGTIME();
  }
  
  digitalWrite(DEVICE_INDICATOR, LOW);
  LCD.clear();
}


/* -------------------------------------------- Call Time Setting -------------------------------------------- */
void SET_CALLTIME(){
  // Set call time 0 - 100
  if(digitalRead(UP_BUTTON) == HIGH){
    delay(50);
    CALL_TIME = CALL_TIME + 1;
    if(CALL_TIME > 100){
      CALL_TIME = 0;
    }
  }
  if(digitalRead(DOWN_BUTTON) == HIGH){
    delay(50);
    CALL_TIME = CALL_TIME - 1;
    if(CALL_TIME < 0){
      CALL_TIME = 100;
    }
  }

  // Calculate digit to show on Display
  int DIGIT_2 = CALL_TIME/100;
  int DIGIT_1 = (CALL_TIME%100)/10;
  int DIGIT_0 = (CALL_TIME%100)%10;

  // Show on LCD
  LCD.setCursor(15, 1);
  LCD.print(CALL_TIME);

  // Show on display
    MAIN_DISPLAY.setDigit(0, 0, DIGIT_0, false);
    MAIN_DISPLAY.setDigit(0, 1, DIGIT_1, false);
    MAIN_DISPLAY.setDigit(0, 2, DIGIT_2, false);

  // if press START, memory and go to next stage
  if(digitalRead(START_BUTTON) == HIGH){
    delay(50);
    EEPROM.update(CALLTIME_ADDR, CALL_TIME);
    SETTING_STAGE = 1;
  }
  delay(200);
}


/* ------------------------------------------ Shooting Time Setting ------------------------------------------ */
void SET_SHOOTINGTIME(){
  // Set shooting time 0 - 600
  if(digitalRead(UP_BUTTON) == HIGH){
    delay(50);
    SHOOTING_TIME =SHOOTING_TIME + 1;
    if(SHOOTING_TIME > 600){
      SHOOTING_TIME = 0;
    }
  }
  if(digitalRead(DOWN_BUTTON) == HIGH){
    delay(50);
    SHOOTING_TIME = SHOOTING_TIME - 1;
    if(SHOOTING_TIME < 0){
      SHOOTING_TIME = 600;
    }
  }

  // Calculate digit to show on Display
  int DIGIT_2 = SHOOTING_TIME/100;
  int DIGIT_1 = (SHOOTING_TIME%100)/10;
  int DIGIT_0 = (SHOOTING_TIME%100)%10;

  // Show on LCD
  LCD.setCursor(15, 1);
  LCD.print(SHOOTING_TIME);

  // Show on display
    MAIN_DISPLAY.setDigit(0, 0, DIGIT_0, false);
    MAIN_DISPLAY.setDigit(0, 1, DIGIT_1, false);
    MAIN_DISPLAY.setDigit(0, 2, DIGIT_2, false);

  // if press START, memory and go to next stage
  if(digitalRead(START_BUTTON) == HIGH){
    delay(50);
    EEPROM.update(SHOOTINGTIME_ADDR, SHOOTING_TIME);
    SETTING_STAGE = 2;
  }
  delay(200);
}
