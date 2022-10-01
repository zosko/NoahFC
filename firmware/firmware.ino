#include <Wire.h>
#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>
#include <PPMReader.h>
#include <ServoTimer2.h>
#include <SimpleKalmanFilter.h>

//#include <SPI.h>
//#include <max7456.h>

// OSD
//Max7456 osd;

// SERVOS
const int PIN_ALERON = 9;
const int PIN_ELEVATOR = 10;
const int PIN_THROTTLE = 11;
ServoTimer2 servoThrottle;
ServoTimer2 servoElevator;
ServoTimer2 servoAleron;

//MPU6050
int pitchAngle = 0;
int rollAngle = 0;
SimpleKalmanFilter kalmanPitch(10, 10, 0.01);
SimpleKalmanFilter kalmanRoll(10, 10, 0.01);

float Cal_GyX, Cal_GyY, Cal_GyZ;
float xAngle, yAngle, zAngle;
const float alpha = 0.96;

//HMC5883L
int headingDegrees = 0;

// PPM
const int PIN_PPM =  3;
PPMReader ppm(PIN_PPM, 5); // (InterruptPin, MaxChannels)
unsigned int ch1 = 1500;
unsigned int ch2 = 1500;
unsigned int ch3 = 1500;
unsigned int ch4 = 1500;
unsigned int ch5 = 1500;

// VOLTAGE READ
float voltage = 0.0;
const int PIN_VOLTAGE = A2;

// LEDS
const int PIN_LED_MODE = 4;
const int PIN_LED_GPS = 5;
const int PIN_LED_POWER = 7;

// GPS
enum navigation_turn {
  DO_NOTHING,
  ARRIVED,
  FORWARD,
  TURN_LEFT,
  TURN_RIGHT,
  TURN_LITTLE_LEFT,
  TURN_LITTLE_RIGHT,
  TURN_AROUND
};
navigation_turn navigation;
NeoGPS::Location_t homeLocation;
static NMEAGPS gps;
gps_fix fix;

int nav_dir = 0;

// LoopTimer
long loop_timer;

void setup() {
  //  SPI.begin();
  Wire.begin();

  pinMode(PIN_VOLTAGE, INPUT);
  pinMode(PIN_LED_MODE, OUTPUT);
  pinMode(PIN_LED_GPS, OUTPUT);
  pinMode(PIN_LED_POWER, OUTPUT);

  servoAleron.attach(PIN_ALERON);
  servoElevator.attach(PIN_ELEVATOR);
  servoThrottle.attach(PIN_THROTTLE);

  gpsPort.attachInterrupt(GPSisr);
  gpsPort.begin(9600);

  ppm.channelValueMaxError = 100; // trashhold PPM for min / max
  ppm.blankTime = 2200;

  loop_timer = micros();

  setupOSD();
  setupMPU6050();
  setupHMC5883L();
  ledStartup();
}

void loop() {
  readPPM();
  readGPS();
  readMPU();
  readHMC5883L();
  readVoltage();
  showOSD_Data();

  if (ch5 < 1300) { // Manual
    pitchAngle = 0;
    rollAngle = 0;
    ledManualMode();
  } else if (ch5 > 1700) { // Return to land
    ch1 = 0;
    ch2 = 0;
    ch3 = 1030;

    switch (navigation) {
      case DO_NOTHING:
        break;
      case ARRIVED:
        ch1 = 2000;
        break;
      case FORWARD:
        break;
      case TURN_LEFT:
        ch1 = 1200;
        break;
      case TURN_RIGHT:
        ch1 = 1800;
        break;
      case TURN_LITTLE_LEFT:
        ch1 = 1300;
        break;
      case TURN_LITTLE_RIGHT:
        ch1 = 1600;
        break;
      case TURN_AROUND:
        ch1 = 2000;
        break;
    }

    navigation = DO_NOTHING;

    ledAngleMode();
  } else { // Angle Mode
    ledAngleMode();
  }

  pitchAngle = kalmanPitch.updateEstimate(pitchAngle);
  rollAngle = kalmanRoll.updateEstimate(rollAngle);

  servoAleron.write(pitchAngle + ch1);
  servoElevator.write(rollAngle + ch2);
  servoThrottle.write(ch3);

  while (micros() - loop_timer < 4000);  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
