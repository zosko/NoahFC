#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>
#include <PPMReader.h> // https://github.com/dimag0g/PPM-reader
#include <Wire.h>
#include <ServoTimer2.h>

// SERVOS
const int PIN_ESC_CONTROLLER  =  6;
const int PIN_LEFT_WING  =  9;
const int PIN_RIGHT_WING =  10;
const int PIN_ELEVATOR   =  11;

ServoTimer2 escController;
ServoTimer2 servoLeftWing;
ServoTimer2 servoRightWing;
ServoTimer2 servoElevator;

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

// GPS
#ifndef NMEAGPS_INTERRUPT_PROCESSING
#error You must define NMEAGPS_INTERRUPT_PROCESSING in NMEAGPS_cfg.h!
#endif
static NMEAGPS gps;
gps_fix fix;
NeoGPS::Location_t homeLocation;

// LoopTimer
long loop_timer;

void setup() {
  Wire.begin();
  //  Serial.begin(9600);
  gpsPort.attachInterrupt(GPSisr);
  gpsPort.begin(9600);

  setupMPU6050();

  ppm.channelValueMaxError = 100; // trashhold PPM for min / max

  servoLeftWing.attach(PIN_LEFT_WING);
  servoRightWing.attach(PIN_RIGHT_WING);
  servoElevator.attach(PIN_ELEVATOR);
  escController.attach(PIN_ESC_CONTROLLER);

  loop_timer = micros();
}

void loop() {
  readPPM();
  readGPS();
  readMPU();

  if (ch5 < 1300) { // Manual
    yAngle = 0;
    xAngle = 0;
  } else if (ch5 > 1700) { // Return to land
    
  }

  servoLeftWing.write(yAngle + ch1);
  servoRightWing.write(yAngle + ch1);
  servoElevator.write(xAngle + ch2);
  escController.write(ch3);

  while (micros() - loop_timer < 20000);  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
