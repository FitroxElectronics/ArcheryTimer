/* -------------------------------------------- Precount Program --------------------------------------------- */
void CALL_TIMER(int CALL_REMAIN){
  LCD.clear();
  // LCD show call time
  LCD.setCursor(0, 0);
  LCD.print(" CALL TIME");

  // Show AB/CD stage on LCD
  if(AB_STAGE == true){
    LCD.setCursor(18, 0);
  LCD.print("AB");
    }
    else{
      LCD.setCursor(18, 0);
  LCD.print("CD");
    }
    
  // Counter program
  while(CALL_REMAIN > 0){
    // Blink AB/CD Light
    if(AB_STAGE == true){
  BLINK_LED(AB_LIGHT);
    }
    else{
      BLINK_LED(CD_LIGHT);
    }

    // Check time and display remaining time
    if(millis() - CURRENT_TIME >= HALF_SECOND){
      CURRENT_TIME = millis();
      HALF_COUNT = HALF_COUNT + 1;
      
      if(HALF_COUNT == 2){
        CALL_REMAIN = CALL_REMAIN - 1;
        HALF_COUNT = 0;
      }

      TIMER_DISPLAY(CALL_REMAIN);
      /*
      if(CALL_REMAIN == 10 || 5 || 4 || 3 || 2 || 1){
        BUZZER_ONLY(1, 0);
      }
      */
    }         // End if(millis() - CURRENT_TIME >= HALF_SECOND)
    
  }         // End while(CALL_REMAIN > 0)

  // if CALL_REMAIN = 0 buzzer and horn make long noise and end function
  if(CALL_REMAIN == 0){
    BUZZER_HORN(1, 1);
    digitalWrite(YELLOW_LIGHT, LOW);
    digitalWrite(GREEN_LIGHT, HIGH);
  }
}         // End CALL_TIMER(int CALL_REMAIN)

/* ---------------------------------------------- Count Program ---------------------------------------------- */
void SHOOTING_TIMER(int SHOOTING_REMAIN){
  LCD.clear();
  // AB/CD Light up
  AB_DISPLAY();
  LCD.setCursor(0, 0);
  LCD.print(" SHOOTING TIME");

  // Counter program
  while(SHOOTING_REMAIN > 0){
    // Check time and display remaining time
    if(millis() - CURRENT_TIME >= HALF_SECOND){
      CURRENT_TIME = millis();
      HALF_COUNT = HALF_COUNT + 1;
      
      if(HALF_COUNT == 2){
        SHOOTING_REMAIN = SHOOTING_REMAIN - 1;
        HALF_COUNT = 0;
      }
      TIMER_DISPLAY(SHOOTING_REMAIN);
    }         // End if(millis() - CURRENT_TIME >= HALF_SECOND)

    // Last 30 second of SHOOTING_REMAIN turn YELLOW light ON
    if(SHOOTING_REMAIN == 30){
      digitalWrite(GREEN_LIGHT, LOW);
      digitalWrite(YELLOW_LIGHT, HIGH);
    }
  }         // End (SHOOTING_REMAIN > 0)

  // if SHOOTING_REAMIN = 0 toggle AB/CD stage, buzzer and horn noise 3 times, RUN_STAGE = false to stop function
  if(SHOOTING_REMAIN == 0){
      RUN_STAGE = false;
      AB_STAGE = !AB_STAGE;
      BUZZER_HORN(3, 0); 
      LCD.clear();
    }
    
}         // End SHOOTING_TIMER(int SHOOTING_REMAIN)
