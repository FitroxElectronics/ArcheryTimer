/* --------------------------------- Builtin Buzzer and External Horn Noise ---------------------------------- */
void BUZZER_HORN(int BEEP_TIME, int BEEP_MODE){
  int BEEP_DELAY;
  // MODE 0 = Short beep, MODE 1 = Long beep
  if(BEEP_MODE == 0){
    BEEP_DELAY = 250;
  }
  else if (BEEP_MODE == 1){
    BEEP_DELAY = 500;
  }

    for(int i = 0; i < BEEP_TIME; i++){
    digitalWrite(BUZZER, HIGH);
    digitalWrite(HORN, HIGH);
    delay(BEEP_DELAY);
    digitalWrite(BUZZER, LOW);
    digitalWrite(HORN, LOW);
    delay(BEEP_DELAY);
    }
}         // End BUZZER_HORN


/* --------------------------------------- Builtin Buzzer Noise Only ----------------------------------------- */
void BUZZER_ONLY(int BUZZER_TIME, int BUZZER_MODE){
  int BUZZER_DELAY;
  // MODE 0 = Short beep, MODE 1 = Long beep
  if(BUZZER_MODE == 0){
    BUZZER_DELAY = 250;
  }
  else if (BUZZER_MODE == 1){
    BUZZER_DELAY = 500;
  }

  if(BUZZER_TIME == 1){
    digitalWrite(BUZZER, HIGH);
    delay(BUZZER_DELAY);
    digitalWrite(BUZZER, LOW);
  }
  else{
    for(int i = 0; i < BUZZER_TIME; i++){
    digitalWrite(BUZZER, HIGH);
    delay(BUZZER_DELAY);
    digitalWrite(BUZZER, LOW);
    delay(BUZZER_DELAY);
  }
  }
}         // End BUZZER_ONLY


/* --------------------------------------------- Blink any LED ----------------------------------------------- */
void BLINK_LED(int BLINK_PIN){
  if(millis() - LAST_BLINK >= 500){
    LAST_BLINK = millis();
    digitalWrite(BLINK_PIN, !digitalRead(BLINK_PIN));
  }
}         // End BLINK_LED
