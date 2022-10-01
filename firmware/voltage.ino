void readVoltage() {
  const float R1 = 100000.0;
  const float R2 = 10000.0;

  int value = analogRead(PIN_VOLTAGE);
  float vout = (value * 5.0) / 1024.0;
  float correction = 0.15; // used to make correction on voltage display
  voltage = vout / (R2 / (R1 + R2)) + correction;
}
