void readVoltage() {
  int value = analogRead(VOLTAGE_READ_PIN);
  float vout = (value * 5.0) / 1024.0;
  voltage = vout / (R2 / (R1 + R2));
  //  Serial.print("[VOLTAGE] ");
  //  Serial.print(voltage);
}
