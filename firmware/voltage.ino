void readVoltage() {
  int value = analogRead(PIN_VOLTAGE);
  float vout = (value * 5.0) / 1024.0;
  float correction = 0.15; // used to make correction on voltage display
  voltage = vout / (R2 / (R1 + R2)) + correction;
}
