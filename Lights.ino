void Led() {


  if ((millis() - delayTime) > 80) { //timer = 20, 0.02sec
    if (count2 < 12) {
      count2++;
      digitalWrite(pinArray[count2], HIGH);

      if (count2 > 2) {
        digitalWrite(pinArray[count2 - 3], LOW);
      }
    }
    if (count2 > 11) {

      count3--;
      digitalWrite(pinArray[count3], HIGH);

      if (count3 < 10) {
        digitalWrite(pinArray[count3 + 3], LOW);
      }
    }
    delayTime = millis();
  }

  if (count2 == 12 && count3 == -3) { //led loop
    count2 = -1;
    count3 = 12;
  }

}   //Led() end

void LedOff() {


  for (int i = 0; i < 10; i++)
    digitalWrite(pinArray[i], LOW);

}
