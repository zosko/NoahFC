#include <Wire.h>
#include <Servo.h>

const int PIN_LEFT_WING  =  9;
const int PIN_RIGHT_WING =  10;
const int PIN_ELEVATOR   =  11;

Servo servoLeftWing;
Servo servoRightWing;
Servo servoElevator;

long loop_timer;

void setup() {
  Serial.begin(9600);

  //Activate the MPU-6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  servoLeftWing.attach(PIN_LEFT_WING);
  servoRightWing.attach(PIN_RIGHT_WING);
  servoElevator.attach(PIN_ELEVATOR);

  loop_timer = micros();
}
void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 4);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();

  int xangle = AcX / 182.04;
  int yangle = AcY / 182.04;

  servoLeftWing.write(yangle + 90);
  servoRightWing.write(yangle + 90);
  servoElevator.write(90 - xangle);

  Serial.print(yangle + 90);
  Serial.print("   ");
  Serial.println(90 - xangle);

  while (micros() - loop_timer < 4000);  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
