#include "Wire.h"
#include "elapsedMillis.h"
#include "SevSeg.h"

//Nrf
#include <SPI.h>
#include "RF24.h"

// nopeus

//calculations
//tire radius ~ 1,9685 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25

#define reed 49 //pin connected to read switch

//storage variables
float radius = 1.968;// tire radius (in inches)- CHANGE THIS FOR YOUR OWN BIKE

int reedVal;
long timer = 0;// time between one full rotation (in ms)
float mph = 0.00;
float mph2 = 0.00;
float mph3 = 0.00;
float circumference;
boolean backlight;

int maxReedCounter = 50;//min time (in ms) of one rotation (for debouncing)
int reedCounter;

int switchState = 0;
// nopeus

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(12, 13);
/**********************************************************/

byte addresses[][6] = {"1Node", "2Node"};

// Used to control whether this node is sending or receiving
bool role = 0;
//Nrf

/*
  #define    MPU9250_ADDRESS            0x68
  #define    MAG_ADDRESS                0x0C

  #define    GYRO_FULL_SCALE_250_DPS    0x00
  #define    GYRO_FULL_SCALE_500_DPS    0x08
  #define    GYRO_FULL_SCALE_1000_DPS   0x10
  #define    GYRO_FULL_SCALE_2000_DPS   0x18

  #define    ACC_FULL_SCALE_2_G        0x00
  #define    ACC_FULL_SCALE_4_G        0x08
  #define    ACC_FULL_SCALE_8_G        0x10
  #define    ACC_FULL_SCALE_16_G       0x18
*/
//float acc;
//float acc2;
//float matka;
//elapsedMillis elapsedmil;


SevSeg sevseg; //Initiate a seven segment controller object
uint8_t d;
//Led
int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int count = 0;
int count2 = -1;
int count3 = 12;
//int timer = 20;
long delayTime;
long SenddelayTime; //Send data
long delayTimeAcc;
long delayTimeVol;
long delayNopeus;
long delayTimeBrake;

float v1;
float kmh1;

//void accelerationSetup(void);
//void Voltage(void);
//void accelerationLoop(void);
uint8_t Off(uint8_t);

//Buttons
// constants won't change. They're used here to set pin numbers:
const int button26Pin = 26;     // the number of the pushbutton pin
const int button28Pin = 28;     // the number of the pushbutton pin

// variables will change:
int buttonState26 = 0;         // variable for reading the pushbutton status
int buttonState28 = 0;

byte oldbutton26 = 0;
byte oldbutton28 = 0;
byte state26 = 0;
byte state28 = 0;
byte pressed26 = 0;
byte pressed28 = 0;
//Buttons

void setup() {

  Serial.begin(115200);
  displaySetup();   //for voltage display

  //calibrationSetup();

  NopeusSetup();
  //voltage
  //Serial.begin(9600);

  //Buttons
  pinMode(button26Pin, INPUT);
  pinMode(button28Pin, INPUT);
  //Buttons

  //led
  for (count = 0; count < 10; count++) {
    pinMode(pinArray[count], OUTPUT);
  }

  //Nrf

  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  // Start the radio listening for data
  radio.startListening();
  //Nrf

  //Acceleration
  //  accelerationSetup();

}   //setup() end

//int res = Voltage(res);

void loop() {
  //int res = Voltage(res);
  //int luku;
  //displayLoop();
  //Nrf
  NopeusLoop();
  /****************** Ping Out Role ***************************/

  if (role == 0)  {
    if ((millis() - SenddelayTime) > 1000) {
      radio.stopListening();                                    // First, stop listening so we can talk.

      //v1 = displayLoop(v1); //get voltage
      kmh1 = getKMH(kmh1);
      //Serial.print("V1 : ");
      //Serial.println(v1);

      Serial.println(F("Now sending"));

      //unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete

      if (!radio.write( &kmh1, sizeof(float) )) {
        Serial.println(F("failed"));
      }


      radio.startListening();                                    // Now, continue listening

      unsigned long started_waiting_at = millis();               // Set up a timeout period, get the current microseconds
      boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

      while ( ! radio.available() ) {                            // While nothing is received
        if (millis() - started_waiting_at > 200 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
        }
      }
/*
      if ( timeout ) {                                            // Describe the results
        Serial.println(F("Failed, response timed out."));
      } else {
        //unsigned long got_time;                                // Grab the response, compare, and send to debugging spew
        float got_value;
        radio.read( &got_value, sizeof(float) );
        //unsigned long end_time = micros();

        // Spew it
        Serial.print(F("Sent "));
        Serial.print(kmh1);
        Serial.print(F(", Got response "));
        Serial.println(got_value);

      }
*/
      SenddelayTime = millis();
    }
  }



  /****************** Pong Back Role ***************************/
  /*
    if ( role == 0 )
    {
      unsigned long got_value;

      if ( radio.available()) {
        // Variable for the received timestamp
        while (radio.available()) {                                   // While there is data ready
          radio.read( &got_value, sizeof(unsigned long) );             // Get the payload
        }

        radio.stopListening();                                        // First, stop listening so we can talk
        radio.write( &got_value, sizeof(unsigned long) );              // Send the final one back.
        radio.startListening();                                       // Now, resume listening so we catch the next packets.
        Serial.print(F("Sent response "));
        Serial.println(got_value);
      }
    }


  */

  /****************** Change Roles via Serial Commands ***************************/
  /*
    if ( Serial.available() )
    {
      char c = toupper(Serial.read());
      if ( c == 'T' && role == 0 ) {
        Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
        role = 1;                  // Become the primary transmitter (ping out)

      } else if ( c == 'R' && role == 1 ) {
        Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
        role = 0;                // Become the primary receiver (pong back)
        radio.startListening();

      }
    }

  */
  //Nrf

  //Buttons
  // read the state of the pushbutton value:

  buttonState26 = digitalRead(button26Pin);
  buttonState28 = digitalRead(button28Pin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  if (buttonState26 == LOW) {
    pressed26 = 0;
  }

  //Button26
  if (buttonState26 == HIGH && !oldbutton26 && !pressed26) {

    if (state26 == 0)
    {
      Serial.println("Button26 On");
      state26 = 1;
      //while (buttonState26 == HIGH) {Led();}


    }
    else
    {
      state26 = 0;
    }
    oldbutton26 = 1;
    pressed26 = 1;

  } else if (buttonState26 == HIGH && oldbutton26 && !pressed26) {

    if (state26 == 1)
    {
      Serial.println("Button26 Off");
      state26 = 0;
      LedOff();
      role = 0;
    }
    else
    {
      state26 = 1;
    }
    oldbutton26 = 0;
    pressed26 = 1;
  } //Button26

  if (buttonState28 == LOW) {
    //Serial.println("28 low");
    pressed28 = 0;
  }

  //Button28
  if (buttonState28 == HIGH && !oldbutton28 && !pressed28) {

    if (state28 == 0)
    {
      Serial.println("Button28 On");
      displayLoop();
      state28 = 1;
      role = 1; //send off
    }
    else
    {
      state28 = 0;
    }
    oldbutton28 = 1;
    pressed28 = 1;

  } else if (buttonState28 == HIGH && oldbutton28 && !pressed28) {

    if (state28 == 1)
    {
      Serial.println("Button28 Off"); //display off
      displayOff();
      role = 0; //send on
      state28 = 0;
    }
    else
    {
      state28 = 1;
    }
    oldbutton28 = 0;
    pressed28 = 1;
  } //Button28

  if (buttonState26 == LOW && state26) {
    Led();
    role = 1; //send off
    
  }
  if (buttonState28 == LOW && state28) {
    displayLoop();
    role = 1; //send off
  }
  //Buttons

}   //loop() end

