void setupHMC5883L() {
//  // 0x1E <- compass address
//
//  //Put the HMC5883 IC into the correct operating mode
//  Wire.beginTransmission(0x1E); //open communication with HMC5883
//  Wire.write(0x02); //select mode register
//  Wire.write(0x00); //continuous measurement mode
//  Wire.endTransmission();
}
void readHMC5883L() {
//  //Tell the HMC5883 where to begin reading data
//  Wire.beginTransmission(0x1E);
//  Wire.write(0x03); //select register 3, X MSB register
//  Wire.endTransmission();
//  Wire.requestFrom(0x1E, 6);
//
//  int xHead = Wire.read() << 8 | Wire.read();
//  int zHead = Wire.read() << 8 | Wire.read();
//  int yHead = Wire.read() << 8 | Wire.read();
//
//  float heading = atan2(yHead, xHead);
//  if (heading < 0) {
//    heading += 2 * PI;
//  }
//  if (heading > 2 * PI) {
//    heading -= 2 * PI;
//  }
//  headingDegrees = heading * 180 / M_PI;
}

// int setpath = 100; //Defines Direction
// int temp = azimuth - setpath;
// int temp2 = 90 + temp;
// myServo.write(temp2);

float azimuth(int y, int x) {
  float azimuth = atan2(y,x) * 180.0 / PI;
  return azimuth < 0 ? 360 + azimuth : azimuth;
}
