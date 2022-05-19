void readVoltage() {
  int value = analogRead(PIN_VOLTAGE);
  float vout = (value * 5.0) / 1024.0;
  voltage = vout / (R2 / (R1 + R2));
}
