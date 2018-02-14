uint8_t OffName(uint8_t d, char nimi[]) {
  Serial.println("Off start");
  while (Serial.available()) {

    uint8_t k;
    k = Serial.read();

    if ( k == 'x' ) {
      Serial.print(nimi);
      Serial.println(" off ");
      d = 'x';
      //LedOff();   //Turn off 2 last led
      displayOff();
      //return d;
      break;
    }
    //return d;
  }
  return d;
}
