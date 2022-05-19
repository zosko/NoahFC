#include <Wire.h>
#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>
#include <PPMReader.h>
#include <ServoTimer2.h>

//#define DEBUG

// SERVOS
const int PIN_ALERON =  9;
const int PIN_ELEVATOR =  10;
const int PIN_THROTTLE =  11;

ServoTimer2 servoThrottle;
ServoTimer2 servoElevator;
ServoTimer2 servoAleron;

//MPU6050
int xAngle = 1500;
int yAngle = 1500;

// PPM
PPMReader ppm(2, 5); // (InterruptPin, MaxChannels)
unsigned int ch1 = 1500;
unsigned int ch2 = 1500;
unsigned int ch3 = 1500;
unsigned int ch4 = 1500;
unsigned int ch5 = 1500;

// VOLTAGE READ
float voltage = 0.0;
const float R1 = 100000.0;
const float R2 = 10000.0;
const int PIN_VOLTAGE = A2;

// GPS
NeoGPS::Location_t homeLocation;
static NMEAGPS gps;
gps_fix fix;
float distanceToHome;
int courseChangeNeeded;

// LoopTimer
long loop_timer;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  Wire.begin();

  gpsPort.attachInterrupt(GPSisr);
  gpsPort.begin(9600);

  setupMPU6050();

  pinMode(PIN_VOLTAGE, INPUT);

  ppm.channelValueMaxError = 100; // trashhold PPM for min / max

  servoAleron.attach(PIN_ALERON);
  servoElevator.attach(PIN_ELEVATOR);
  servoThrottle.attach(PIN_THROTTLE);

  loop_timer = micros();
}

void loop() {
  readPPM();
  readGPS();
  readMPU();
  readVoltage();
  debug();
  
  if (ch5 < 1300) { // Manual
    yAngle = 0;
    xAngle = 0;
  } else if (ch5 > 1700) { // Return to land

  }

  servoAleron.write(yAngle + ch1);
  servoElevator.write(xAngle + ch2);
  servoThrottle.write(ch3);

  while (micros() - loop_timer < 4000);  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
