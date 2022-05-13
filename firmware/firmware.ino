#include <Wire.h>
#include <SPI.h>
#include <NeoHWSerial.h>
#include <NeoSWSerial.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SH110X.h>
//#include <PPMReader.h> // https://github.com/dimag0g/PPM-reader
//#include <ArduPID.h>           // https://github.com/PowerBroker2/ArduPID
#include <TinyGPSPlus.h>       // https://github.com/mikalhart/TinyGPSPlus
//#include <Adafruit_MPU6050.h>  // https://github.com/adafruit/Adafruit_MPU6050
//#include <Adafruit_Sensor.h>
//#include <ServoTimer2.h>  // alternate


//#define i2c_Address 0x3c
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 64
//#define OLED_RESET -1
//Adafruit_SH1106G displayOled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// PPM
const int PPMChannels = 5; // Max channels
const int PPMinput = 3; // Must be interrupt
//PPMReader ppm(PPMinput, PPMChannels);
unsigned int ch1 = 0;
unsigned int ch2 = 0;
unsigned int ch3 = 0;
unsigned int ch4 = 0;
unsigned int mode = 0;

// PIDS ROLL
//ArduPID pidRoll;
//double inputRoll;
//double outputRoll;
//double setpointRoll = 0.0;
//const double pRoll = 10.0;
//const double iRoll = 0.01;
//const double dRoll = 5.0;

// PIDS PITCH
//ArduPID pidPitch;
//double inputPitch;
//double outputPitch;
//double setpointPitch = 0.0;
//const double pPitch = 10.0;
//const double iPitch = 0.01;
//const double dPitch = 5.0;

// SIGNAL LEDS
//const int LED_PWR = 2;
//const int LED_GPS = 4;
//const int LED_MODE = 5;

// SERVOS
//ServoTimer2 servoLeft;
//ServoTimer2 servoRight;
//ServoTimer2 servoTail;
//const int LEFT_WING = 9;
//const int RIGHT_WING = 10;
//const int TAIL_WING = 6;

// VOLTAGE READ
//float voltage = 0.0;
//const float R1 = 100000.0;
//const float R2 = 10000.0;
//const int VOLTAGE_READ_PIN = A2;

// MPU6050
//Adafruit_MPU6050 mpu;
//sensors_event_t a, g, temp;

// GPS
volatile TinyGPSPlus gps;
double home_lat = 0.0;
double home_lng = 0.0;

NeoSWSerial debug(4, 3);


//long loop_timer;

void setup() {
  
  NeoSerial.attachInterrupt(readGPS);
  NeoSerial.begin(9600);
  
  debug.begin(9600);
  debug.println("------- STARTED -------");
  
//  pinMode(13, OUTPUT);
  //  pinMode(LED_PWR, OUTPUT);
  //  pinMode(LED_MODE, OUTPUT);
  //  pinMode(LED_GPS, OUTPUT);



  //GPS Setup

  //  servoLeft.attach(LEFT_WING);
  //  servoRight.attach(RIGHT_WING);
  //  servoTail.attach(TAIL_WING);

  // MPU6050 setup
  //  mpu.begin();
  //  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  //  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  //  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // PPM setup
  //  ppm.channelValueMaxError = 100; // trashhold PPM for min / max

  // PID setup
  //  pidRoll.begin(&inputRoll, &outputRoll, &setpointRoll, pRoll, iRoll, dRoll);
  //  pidRoll.setOutputLimits(-45, 45);
  //  pidRoll.setWindUpLimits(-6, 6);
  //  pidRoll.start();
  //
  //  // PID setup
  //  pidPitch.begin(&inputPitch, &outputPitch, &setpointPitch, pPitch, iPitch, dPitch);
  //  pidPitch.setOutputLimits(-45, 45);
  //  pidPitch.setWindUpLimits(-6, 6);
  //  pidPitch.start();

  //Voltage Pin
  //  pinMode(VOLTAGE_READ_PIN, INPUT);

//  loop_timer = micros();

//  digitalWrite(13, HIGH);
//  delay(250);
//  displayOled.begin(i2c_Address, true);
//  displayOled.setTextSize(1);
//  displayOled.setTextColor(SH110X_WHITE);
//  displayOled.setCursor(0, 0);
//  displayOled.println("NoahFC started");
//  displayOled.display();
  
//  delay(2000);
//  digitalWrite(13, LOW);
}

void loop() {
  displayInfo();
  //  readVoltage();
  //  readPPM();
  //  leds();
  //  setHomePosition();
  //  pidRoll.compute();
  //  pidPitch.compute();
  //  mpu.getEvent(&a, &g, &temp);

  // Servos
  //  inputRoll = a.acceleration.y;
  //  int mapRoll = map(outputRoll, -45, 45, 2000, 1000);
  //  servoLeft.write(mapRoll);
  //  servoRight.write(mapRoll);

  //  inputPitch = a.acceleration.x;
  //  int mapPitch = map(outputPitch, -45, 45, 2000, 1000);
  //  servoTail.write(mapPitch);

  // 20000 - 50hz
  // 4000 - 250Hz
//  while (micros() - loop_timer < 4000);  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
//  loop_timer = micros();
}
