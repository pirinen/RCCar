void Led() {

  for (count = 0; count < 9; count++) {
    digitalWrite(pinArray[count], HIGH);
    delay(timer);
    digitalWrite(pinArray[count + 1], HIGH);
    delay(timer);
    digitalWrite(pinArray[count + 2], HIGH);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer * 2);
    //digitalWrite(pinArray[count] + 1, LOW);
  }
  for (count = 9; count > 1; count--) {
    digitalWrite(pinArray[count], HIGH);
    delay(timer);
    digitalWrite(pinArray[count - 1], HIGH);
    delay(timer);
    digitalWrite(pinArray[count - 2], HIGH);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer * 2);
    //digitalWrite(pinArray[count] - 1, LOW);
  }

}   //Led() end

void LedOff() {

  digitalWrite(pinArray[0], LOW);
  digitalWrite(pinArray[1], LOW);
}