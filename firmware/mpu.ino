void setupMPU6050() {
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  //MPU6050 Clock Type
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x03); // Selection Clock 'PLL with Z axis gyroscope reference'
  Wire.endTransmission();

  //Configure the accelerometer
  //  0x00    ±2     16384
  //  0x08    ±4     8192
  //  0x10    ±8     4096
  //  0x18    ±16    2048
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  //Configure the gyro
  //  0x00     250   [degree/sec]
  //  0x08     500   [degree/sec]
  //  0x10    1000   [degree/sec]
  //  0x18    2000   [degree/sec]
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x18);
  Wire.endTransmission();

  //MPU6050 DLPF(Digital Low Pass Filter)
  // 0x00    Accel BW 260Hz, Delay 0ms / Gyro BW 256Hz, Delay 0.98ms, Fs 8KHz
  // 0x01    Accel BW 184Hz, Delay 2ms / Gyro BW 188Hz, Delay 1.9ms, Fs 1KHz
  // 0x02    Accel BW 94Hz, Delay 3ms / Gyro BW 98Hz, Delay 2.8ms, Fs 1KHz
  // 0x03    Accel BW 44Hz, Delay 4.9ms / Gyro BW 42Hz, Delay 4.8ms, Fs 1KHz
  // 0x04    Accel BW 21Hz, Delay 8.5ms / Gyro BW 20Hz, Delay 8.3ms, Fs 1KHz
  // 0x05    Accel BW 10Hz, Delay 13.8ms / Gyro BW 10Hz, Delay 13.4ms, Fs 1KHz
  // 0x06    Accel BW 5Hz, Delay 19ms / Gyro BW 5Hz, Delay 18.6ms, Fs 1KHz
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x00);
  Wire.endTransmission();
}
void readMPU() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();
  int16_t Tmp = Wire.read() << 8 | Wire.read();
  int16_t GyX = Wire.read() << 8 | Wire.read();
  int16_t GyY = Wire.read() << 8 | Wire.read();
  int16_t GyZ = Wire.read() << 8 | Wire.read();

  // Convert accelerometer to gravity value
  float GAcX = (float) AcX / 4096.0;
  float GAcY = (float) AcY / 4096.0;
  float GAcZ = (float) AcZ / 4096.0;

  float acc_y = atan (GAcY / sqrt(GAcX * GAcX + GAcZ * GAcZ)) * 57.29577951;
  float acc_x = - atan (GAcX / sqrt(GAcY * GAcY + GAcZ * GAcZ)) * 57.29577951;
  float acc_z = atan (GAcZ / sqrt(GAcX * GAcX + GAcZ * GAcZ)) * 57.29577951;

  // Calculate Pitch, Roll & Yaw from Gyroscope value reflected cumulative time factor
  Cal_GyX += GyX * 0.000244140625;
  Cal_GyY += GyY * 0.000244140625;
  Cal_GyZ += GyZ * 0.000244140625;

  xAngle = alpha * ((GyX * 0.000244140625) + xAngle) + (1 - alpha) * acc_x;
  yAngle = alpha * ((GyY * 0.000244140625) + yAngle) + (1 - alpha) * acc_y;
  zAngle += GyZ * 0.000244140625;

  pitchAngle = (yAngle * 10) * -1;
  rollAngle = xAngle * 10;
}
