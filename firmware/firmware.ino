#include <Wire.h>
#include <Servo.h>
#include <PPMReader.h> // https://github.com/dimag0g/PPM-reader
#include <ArduPID.h> // https://github.com/PowerBroker2/ArduPID
#include <TinyGPSPlus.h> // https://github.com/mikalhart/TinyGPSPlus
#include <Adafruit_MPU6050.h> // https://github.com/adafruit/Adafruit_MPU6050
#include <Adafruit_Sensor.h>
#include <NeoSWSerial.h> // https://github.com/SlashDevin/NeoSWSerial
//#include <ServoTimer2.h> // alternate

// PPM
const int PPMChannels = 5; // Max channels
int PPMinput = 3; // Must be interrupt
PPMReader ppm(PPMinput, PPMChannels);
unsigned ch1 = 0;
unsigned ch2 = 0;
unsigned ch3 = 0;
unsigned ch4 = 0;
unsigned mode = 0;

// PIDS ROLL
ArduPID pidRoll;
double inputRoll;
double outputRoll;
double setpointRoll = 0;
double pRoll = 10;
double iRoll = 0.01;
double dRoll = 5;

// PIDS PITCH
ArduPID pidPitch;
double inputPitch;
double outputPitch;
double setpointPitch = 0;
double pPitch = 10;
double iPitch = 0.01;
double dPitch = 5;

// SIGNAL LEDS
const int LED_PWR = 2;
const int LED_GPS = 4;
const int LED_MODE = 5;

// SERVOS
Servo servoLeft;
Servo servoRight;
Servo servoTail;
const int LEFT_WING = 9;
const int RIGHT_WING = 10;
const int TAIL_WING = 6;

// VOLTAGE READ
float voltage = 0.0;
float R1 = 100000.0;
float R2 = 10000.0;
const int VOLTAGE_READ_PIN = A2;

// MPU6050
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

// GPS
TinyGPSPlus gps;
static const int RXPin = 7;
static const int TXPin = 8;
NeoSWSerial gpsSerial(RXPin, TXPin);

long loop_timer;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);

  pinMode(LED_PWR, OUTPUT);
  pinMode(LED_MODE, OUTPUT);
  pinMode(LED_GPS, OUTPUT);

  servoLeft.attach(LEFT_WING);
  servoRight.attach(RIGHT_WING);
  servoTail.attach(TAIL_WING);

  // MPU6050 setup
  if (!mpu.begin()) {
    MPU_missing();
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // PPM setup
  ppm.channelValueMaxError = 100; // trashhold PPM for min / max

  // PID setup
  pidRoll.begin(&inputRoll, &outputRoll, &setpointRoll, pRoll, iRoll, dRoll);
  pidRoll.setOutputLimits(-45, 45);
  pidRoll.setWindUpLimits(-6, 6);
  pidRoll.start();

  // PID setup
  pidPitch.begin(&inputPitch, &outputPitch, &setpointPitch, pPitch, iPitch, dPitch);
  pidPitch.setOutputLimits(-45, 45);
  pidPitch.setWindUpLimits(-6, 6);
  pidPitch.start();

  //Voltage Pin
  pinMode(VOLTAGE_READ_PIN, INPUT);

  loop_timer = micros();

  digitalWrite(LED_PWR, HIGH);
}

void loop() {
  readVoltage();
  readPPM();
  leds();
  pidRoll.compute();
  pidPitch.compute();
  mpu.getEvent(&a, &g, &temp);

  // Servos
  inputRoll = a.acceleration.y;
  inputPitch = a.acceleration.x;
  servoLeft.write(outputRoll + 90);
  servoRight.write(90 - outputRoll);
  servoTail.write(outputPitch + 90);

  if (gpsSerial.available()) {
    char c = gpsSerial.read();
    gps.encode(c);
    digitalWrite(LED_GPS, HIGH);
  }

//  Serial.print("Valid: ");
//  Serial.print(gps.location.isValid());
//  Serial.print("  Sats: ");
//  Serial.print(gps.satellites.value());
//  Serial.print("  Lat: ");
//  Serial.print(gps.location.lat());
//  Serial.print("  Lon: ");
//  Serial.println(gps.location.lng());

  digitalWrite(LED_GPS, gps.location.isValid());
  while (micros() - loop_timer < 4000); //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
