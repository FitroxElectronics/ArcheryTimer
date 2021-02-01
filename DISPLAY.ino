/* ---------------------------------------------- Timer Display ---------------------------------------------- */
void TIMER_DISPLAY(int TIME_REMAIN) {
  // Calculate Second to Minute:Second
  int MINUTE_DISPLAY = TIME_REMAIN / 60;
  int SECOND_DISPLAY = TIME_REMAIN % 60;
  // Separate all digit
  int MINUTE_10 = MINUTE_DISPLAY / 10;            // XX digit
  int MINUTE_0 = MINUTE_DISPLAY % 10;             // X digit
  int SECOND_10 = SECOND_DISPLAY / 10;            // XX digit
  int SECOND_0 = SECOND_DISPLAY % 10;             // X digit

  // Show minute remaining
  if (MINUTE_DISPLAY < 10) {
    MAIN_DISPLAY.setDigit(0, 3, MINUTE_0, false);     // Show only X minute
  }
  MAIN_DISPLAY.setDigit(0, 3, MINUTE_0, false);     // Show only X minute

  // Blink colon sign
  if (COLON == true) {
    MAIN_DISPLAY.setDigit(0, 2, 8, true);
    COLON = false;
  } 
  else {
    MAIN_DISPLAY.setDigit(0, 2, 8, false);
    COLON = true;
  }

  // Show second remaining
  if (SECOND_DISPLAY < 10) {
    MAIN_DISPLAY.setDigit(0, 1, 0, false);
    MAIN_DISPLAY.setDigit(0, 0, SECOND_0, false);
  }
  MAIN_DISPLAY.setDigit(0, 1, SECOND_10, false);
  MAIN_DISPLAY.setDigit(0, 0, SECOND_0, false);

}         // End TIMER_DISPLAY(int TIME_REMAIN)


/* ------------------------------------------- AB/CD Stage Display ------------------------------------------- */
void AB_DISPLAY() {
  if (AB_STAGE == true) {
    MAIN_DISPLAY.setChar(0, 4, 'a', false);
    digitalWrite(AB_LIGHT, HIGH);
    digitalWrite(CD_LIGHT, LOW);
  }
  else {
    MAIN_DISPLAY.setChar(0, 4, 'b', false);
    digitalWrite(AB_LIGHT, LOW);
    digitalWrite(CD_LIGHT, HIGH);
  }
}
