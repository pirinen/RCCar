void displaySetup() {

  byte numDigits = 4;
  byte digitPins[] = {30, 32, 34, 36};
  byte segmentPins[] = {38, 40, 42, 44, 46, 48, 50, 52};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

}

void displayOff() {

  //sevseg.blank();
  sevseg.setNumber(0000, 0);
  sevseg.refreshDisplay(); // Must run repeatedly
  //sevseg.setBrightness(0);
  //sevseg.refreshDisplay();
}

/*
  int Voltage(int result) {

  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  result = voltage;
  Serial.println(voltage);
  delay(500);
  return result;

  }
*/
//int result = 1245;
void displayLoop() {

  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);

  sevseg.setNumber(voltage, 3);
  sevseg.refreshDisplay(); // Must run repeatedly

}

