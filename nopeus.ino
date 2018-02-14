//bike speedometer
//by Amanda Ghassaei 2012
//https://www.instructables.com/id/Arduino-Bike-Speedometer/

/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

*/

//calculations
//tire radius ~ 1,9685 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25

void NopeusSetup() {

  reedCounter = maxReedCounter;
  circumference = 2 * 3.141593 * radius;
  //pinMode(1, OUTPUT); //tx, display?
  pinMode(reed, INPUT);
  pinMode(51, OUTPUT); //Led

  // TIMER SETUP- the timer interrupt allows preceise timed measurements of the reed switch
  //for mor info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  //END TIMER SETUP

  //Serial.begin(9600);
}


ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (reedVal) { //if reed switch is closed
    if (reedCounter == 0) { //min time between pulses has passed
      mph = (91.4 * float(circumference)) / float(timer); //calculate miles per hour
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else {
      if (reedCounter > 0) { //don't let reedCounter go negative
        reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else { //if reed switch is open
    if (reedCounter > 0) { //don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 100) {
    mph = 0;//if no new pulses from reed switch- tire is still, set mph to 0
  }
  else {
    timer += 1;//increment timer
  }
}
float getKMH (float kmh)
{
  kmh = mph;
  return kmh;
}

void displayMPH() {
  
  Serial.write(12);//clear
  Serial.write("Speed = ");
  Serial.write(13);//start a new line
  Serial.print(mph);
  Serial.println(" km/h ");
  //Serial.write("0.00 MPH ");
}

void NopeusLoop() {
  //print mph once a second
  if ((millis() - delayNopeus) > 1000) {
    displayMPH();
    delayNopeus = millis();
  }
  digitalWrite(51, LOW);
  //Serial.println(mph);
  //Serial.println(mph2);
  mph3 = mph;
  if (mph < mph2) {

    //Serial.println ("pienenee");

    digitalWrite(51, HIGH);
  }
  mph2 = mph;
}





