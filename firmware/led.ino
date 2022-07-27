void ledStartup() {
  digitalWrite(PIN_LED_MODE, HIGH);
  delay(200);
  digitalWrite(PIN_LED_MODE, LOW);
  digitalWrite(PIN_LED_GPS, HIGH);
  delay(200);
  digitalWrite(PIN_LED_GPS, LOW);
  digitalWrite(PIN_LED_POWER, HIGH);
  delay(200);
}
void ledManualMode() {
  digitalWrite(PIN_LED_MODE, LOW);
}
void ledAngleMode() {
  digitalWrite(PIN_LED_MODE, HIGH);
}
void ledGpsReceive() {
  digitalWrite(PIN_LED_GPS, HIGH);
}
void ledGpsIdle() {
  digitalWrite(PIN_LED_GPS, LOW);
}
