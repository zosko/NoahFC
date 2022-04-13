#include <Wire.h>
#include <Servo.h>
#include <PPMReader.h> //https://github.com/dimag0g/PPM-reader
#include <ArduPID.h> //https://github.com/PowerBroker2/ArduPID

const int PPMChannels = 6;
int PPMin = 3;
PPMReader ppm(PPMin, PPMChannels);

ArduPID pid;
double input;
double output;
double setpoint = 0;
double p = 10;
double i = 1;
double d = 0.5;

Servo servo;
Servo servo2;

int angle, angle2, yangle;
long loop_timer;

const int MPU_addr = 0x68;
int16_t acc_x, acc_y, acc_z, temperature, gyro_x, gyro_y, gyro_z;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  setup_mpu6050();

  pid.begin(&input, &output, &setpoint, p, i, d);
  pid.setOutputLimits(0, 90);
  pid.setBias(255.0 / 2.0);
  pid.setWindUpLimits(-10, 10);
  pid.start();

  servo.attach(9);
  servo2.attach(10);

  loop_timer = micros();
}

void loop() {
  read_mpu6050();
  readPPM();
  pid.compute();

  input = acc_y;
  servo.write(input + 90);
  servo2.write(90 - input);
  
  //  yangle = acc_y / 182.04;
  //  servo.write(yangle + 90);
  //  servo2.write(90 - yangle);

  while (micros() - loop_timer < 4000); //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();

}
void read_mpu6050() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr, 14); //Request 14 bytes from the MPU-6050

  acc_x = Wire.read() << 8 | Wire.read();
  acc_y = Wire.read() << 8 | Wire.read();
  acc_z = Wire.read() << 8 | Wire.read();

  temperature = Wire.read() << 8 | Wire.read();

  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
}

void setup_mpu6050() {

  //Activate the MPU-6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}

void readPPM() {
  unsigned ch1 = ppm.latestValidChannelValue(1, 0);
  unsigned ch2 = ppm.latestValidChannelValue(2, 0);
  unsigned ch3 = ppm.latestValidChannelValue(3, 0);
  unsigned ch4 = ppm.latestValidChannelValue(4, 0);

  Serial.print("[CH1] ");
  Serial.print(ch1);
  Serial.print(" [CH2] ");
  Serial.print(ch2);
  Serial.print(" [CH3] ");
  Serial.print(ch3);
  Serial.print(" [CH4] ");
  Serial.print(ch4);
  Serial.println();
}
