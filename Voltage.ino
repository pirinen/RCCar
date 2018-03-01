void displaySetup() {
  Serial.println("display setup");
  byte numDigits = 4;
  byte digitPins[] = {30, 32, 34, 36};
  byte segmentPins[] = {38, 40, 42, 44, 46, 48, 45, 43};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

}

void displayOff() {
  Serial.println("display off");
  sevseg.blank();
  
  //byte hardwareConfig = 3;
  //sevseg.begin(hardwareConfig, numDigits, digitPins);
  
  //sevseg.setNumber(0000, 0);
  //sevseg.refreshDisplay(); // Must run repeatedly
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
  //Serial.println("Voltage loop start");
  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  v1 = voltage;
  
  //if ((millis() - delayTimeVol) > 1000) { //timer = 1000, 1.00sec
    //Serial.print("Voltage : ");
    //Serial.println(voltage);
    //while not (radio.available(0))
    //{
    //radio.write(&voltage, sizeof(voltage));
    //}
    //delayTimeVol = millis();
  //}

  //kmh1 = getKMH();
  sevseg.setNumber(kmh1, 3);
  Serial.print("Nopeus : ");
  Serial.println(kmh1);
  sevseg.refreshDisplay(); // Must run repeatedly
  //return v1;
}

