void leds() {
  if (mode < 1300) {
    digitalWrite(LED_MODE, LOW);
    digitalWrite(LED_GPS, LOW);
  } else if (mode > 1400 && mode < 1500) {
    digitalWrite(LED_MODE, HIGH);
    digitalWrite(LED_GPS, LOW);
  } else if (mode > 1600) {
    digitalWrite(LED_MODE, LOW);
    digitalWrite(LED_GPS, HIGH);
  }
}
void MPU_missing() {
  while(1) {
    digitalWrite(LED_GPS, HIGH);
    digitalWrite(LED_MODE, HIGH);
    digitalWrite(LED_PWR, HIGH);
    delay(500);
    digitalWrite(LED_GPS, LOW);
    digitalWrite(LED_MODE, LOW);
    digitalWrite(LED_PWR, LOW);
    delay(500);
  }
}
