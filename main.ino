//Calibration
/*
  #include <Arduino.h>
  #include <I2Cdev.h>
  #include <ms5611.h>
  #include <vertaccel.h>
  #include <EEPROM.h>
  #include <LightInvensense.h>
  #include <avr/pgmspace.h>
  #include <accelcalibrator.h>
  #include "Wire.h"
  #include "elapsedMillis.h"

  AccelCalibrator calibrator;

  const char usage01[] PROGMEM  = "-------------------------";
  const char usage02[] PROGMEM  = "ACCELEROMETER CALIBRATION";
  const char usage03[] PROGMEM  = "-------------------------";
  const char usage04[] PROGMEM  = "";
  const char usage05[] PROGMEM  = "Commands :";
  const char usage06[] PROGMEM  = "  d : display current accel vector";
  const char usage07[] PROGMEM  = "  m : measure accel vertor for calibration";
  const char usage08[] PROGMEM  = "  c : start calibration";
  const char usage09[] PROGMEM  = "  r : restart calibration to the beginning";
  const char usage10[] PROGMEM  = "";
  const char usage11[] PROGMEM  = "Procedure :";
  const char usage12[] PROGMEM  = "  The accelerometer calibration procedure";
  const char usage13[] PROGMEM  = "  need five accel vectors from the five upper ";
  const char usage14[] PROGMEM  = "  orientations. That is to say with the";
  const char usage15[] PROGMEM  = "  accelerometer pointing :";
  const char usage16[] PROGMEM  = "    -> toward the sky, flat on the groud";
  const char usage17[] PROGMEM  = "    -> toward the left on it's left side";
  const char usage18[] PROGMEM  = "    -> toward the right on it's right side";
  const char usage19[] PROGMEM  = "    -> toward you on it's bottom side";
  const char usage20[] PROGMEM  = "    -> back to you, on it's top side";
  const char usage21[] PROGMEM  = "";
  const char usage22[] PROGMEM  = "  For each measure :";
  const char usage23[] PROGMEM  = "  1) You can check the current accel vector";
  const char usage24[] PROGMEM  = "     with multiple 'd' command.";
  const char usage25[] PROGMEM  = "  2) Record the accel vector with the 'm' command";
  const char usage26[] PROGMEM  = "     This can be done multiple times for each orientations";
  const char usage27[] PROGMEM  = "";
  const char usage28[] PROGMEM  = "  Once the five orientations recorded. You can";
  const char usage29[] PROGMEM  = "  launch the calibration procedure with the 'c'";
  const char usage30[] PROGMEM  = "  command. Use the 'd' command  to check the result.";
  const char usage31[] PROGMEM  = "  The distance must be as close as possible to 1.000.";
  const char usage32[] PROGMEM  = "  If you are not satisfied by the result. Make more";
  const char usage33[] PROGMEM  = "  measures or reset teh calibration with the 'r' command.";
  const char usage34[] PROGMEM  = "-------------------------";
  const char usage35[] PROGMEM  = "";

  const char* const usage[] PROGMEM = { usage01, usage02, usage03, usage04, usage05,
                                      usage06, usage07, usage08, usage09, usage10,
                                      usage11, usage12, usage13, usage14, usage15,
                                      usage16, usage17, usage18, usage19, usage20,
                                      usage21, usage22, usage23, usage24, usage25,
                                      usage26, usage27, usage28, usage29, usage30,
                                      usage31, usage32, usage33, usage34, usage35};
  #define USAGE_TEXT_LINE_COUNT 33
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

  const char separatorMsg[] PROGMEM  = "-------------------------";
  const char measureReadyMsg[] PROGMEM  = "Ready to make measure.";
  const char measureAndCalibrateReadyMsg[] PROGMEM  = "Ready to make measure or calibration.";
  const char calibrationNotReadyMsg[] PROGMEM  = "Not enough measures to calibrate !";

  const char measureValidMsg[] PROGMEM  = "GOOD measure, recorded for calibration";
  const char measureInvalidMsg01[] PROGMEM  = "BAD measure, not recorded, possible problems are :";
  const char measureInvalidMsg02[] PROGMEM  = "-> ambiguous orientation";
  const char measureInvalidMsg03[] PROGMEM  = "-> orientation already done with lower standard deviation";
  const char* const measureInvalidMsg[] PROGMEM = {measureInvalidMsg01, measureInvalidMsg02, measureInvalidMsg03};
  #define MEASURE_INVALID_LINE_COUNT 3

  const char resetMsg[] PROGMEM  = "Reset calibration !";
  const char waitMsg[] PROGMEM  = "Don't move the accelerometer and wait...";
  const char recordMsg[] PROGMEM  = "Starting measure...";


  const char calMsgB01[] PROGMEM  = "-------------------------";
  const char calMsgB02[] PROGMEM  = "CALIBRATION DONE ";
  const char calMsgB03[] PROGMEM  = "-------------------------";
  const char calMsgB04[] PROGMEM  = "";
  const char calMsgB05[] PROGMEM  = "Here the new calibration coefficients :";
  const char calMsgB06[] PROGMEM  = "";
  const char* const calMsgB[] PROGMEM = {calMsgB01, calMsgB02, calMsgB03, calMsgB04, calMsgB05, calMsgB06};
  #define CALB_TEXT_LINE_COUNT 6

  const char calMsgE01[] PROGMEM  = "";
  const char calMsgE02[] PROGMEM  = "Run multiple 'd' command to check the result.";
  const char calMsgE03[] PROGMEM  = "-------------------------";
  const char* const calMsgE[] PROGMEM = {calMsgE01, calMsgE02, calMsgE03};
  #define CALE_TEXT_LINE_COUNT 3

  float acc;
  float acc2;
  float matka;
  elapsedMillis elapsedmil;*/
//Calibration end
#include "Wire.h"
#include "elapsedMillis.h"
#include "SevSeg.h"

// Remote
#include <IRremote.h>
int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;
// Remote

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

float acc;
float acc2;
float matka;
elapsedMillis elapsedmil;


SevSeg sevseg; //Initiate a seven segment controller object
uint8_t d;
//Led
int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int count = 0;
int count2 = -1;
int count3 = 12;
int timer = 20;
long delayTime;
long delayTimeAcc;

//void accelerationSetup(void);
//void Voltage(void);
//void accelerationLoop(void);
uint8_t Off(uint8_t);

void setup() {

  //led
  for (count = 0; count < 10; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
  //voltage
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  //Acceleration
  accelerationSetup();
  //displaySetup();   //for voltage display

  byte numDigits = 4;
  byte digitPins[] = {30, 32, 34, 36};
  byte segmentPins[] = {38, 40, 42, 44, 46, 48, 50, 52};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

  //calibrationSetup();
  //Serial.begin(115200);

}   //setup() end
//int res = Voltage(res);
void loop() {
  //int res = Voltage(res);
  int luku;
  //res = Voltage(res);
  //Serial.println(res);
  //sevseg.setNumber(res, 3);
  //sevseg.refreshDisplay(); // Must run repeatedly

  //Remote
  if (irrecv.decode(&results))
  {
    Serial.println(results.value/*, HEX*/);
    irrecv.resume(); // Receive the next value
    luku = results.value;

    Serial.print("luku : ");
    Serial.println(luku);


  }
  //1 = 2534850111
  //2 = 1033561079
  //3 = 1635910171
  //0 = 3238126971

  //Remote
  //if ( luku == -16833 ) { //Led while
  //Led();
  //}
  //else if ( luku == -6789) {
  //char nimi[] = "Led";
  //d = OffName(d, nimi);
  ////Off(d);

  //delayTime = millis();
  //Serial.println(delayTime);
  if ( Serial.available() ) {

    //uint8_t d;
    while ( Serial.available() ) {
      d = Serial.read();
      while ( d == 'l' ) { //Led while
        
        displayLoop();
        accelerationLoop();
        
        if ((millis() - delayTime) > 80) { //timer = 20, 0.02sec
          if (count2 < 12) {
            count2++;
            //count3++;
            //Serial.print("Count2 : ");
            //Serial.println(count2);
            digitalWrite(pinArray[count2], HIGH);

            if (count2 > 2) {
              digitalWrite(pinArray[count2 - 3], LOW);
            }
          }
          if (count2 > 11) {

            count3--;
            //Serial.print("Count3 : ");
            //Serial.println(count3);
            digitalWrite(pinArray[count3], HIGH);

            if (count3 < 10) {
              digitalWrite(pinArray[count3 + 3], LOW);
            }
          }
          delayTime = millis();
        }
        //Serial.println(millis());

        char nimi[] = "Led";
        d = OffName(d, nimi);

        if (count2 == 12 && count3 == -3) { //led loop
          count2 = -1;
          count3 = 12;
        }
      }
      //count2 = -1;  //Jatkuu minne jäi
      //count3 = 12;

      //Led while
      if ( d == 'e') {    //Calibration while

        //Calibration();
        //Calibration calib;
        //Calibration.calibrationSetup();
        //calibrationSetup();
      } //Calibration while

      else if ( d == 'v') {  //Voltage
        while ( d == 'v') {
          //Voltage();
          displayLoop();
          char nimi[] = "Voltage";
          d = OffName(d, nimi);
          //d = Off(d);

        } //While
      }   //Voltage
      else if ( d == 'a') { //Acceleration
        while ( d == 'a') {
          //Acceleration();
          accelerationLoop();
          char nimi[] = "Acceleration";
          d = OffName(d, nimi);
          ////Off(d);
        } //While
      } //Acceleration


    } //while Serial
  }   //if Serial

  //Led();
  //Voltage();

  //calibrationLoop();

}   //loop() end

