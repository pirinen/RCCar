void Voltage() {

  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  delay(500);

}
