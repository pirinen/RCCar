/*void Acceleration() {
  Serial.println("Acceleration");
  delay(1000);
  }
*//*
  #include "Wire.h"
  #include "elapsedMillis.h"

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
*/
void I2Cread(uint8_t, uint8_t, uint8_t, uint8_t*);
void I2CwriteByte(uint8_t, uint8_t, uint8_t);
void accelerationSetup(void);
void accelerationLoop(void);

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}



void accelerationSetup() {
  // Arduino initializations
  Wire.begin();
  //Serial.begin(115200);
  //Serial.begin(9600);

  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
}

long int cpt = 0;

void accelerationLoop() {
  // put your main code here, to run repeatedly:
  unsigned long StartTime;
  unsigned long CurrentTime;
  unsigned long ElapsedTime;

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);


  // Create 16 bits values from 8 bits data

  // Accelerometer
  int16_t ax = -(Buf[0] << 8 | Buf[1]);
  int16_t ay = -(Buf[2] << 8 | Buf[3]);
  int16_t az = Buf[4] << 8 | Buf[5];

  // Gyroscope
  int16_t gx = -(Buf[8] << 8 | Buf[9]);
  int16_t gy = -(Buf[10] << 8 | Buf[11]);
  int16_t gz = Buf[12] << 8 | Buf[13];

  if (ax <= -200 || ax >= 200)
  {
    acc = ax * 0.001 * 9.8;
  }

  //if (acc != acc2)
  //{
  acc2 = acc;
  Serial.print(" Acc = ");
  Serial.print(acc, 2);
  Serial.print(" m/s2 ");
  Serial.println("");
  //}
  delay(250);
}

