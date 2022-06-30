void debug() {
  #ifdef DEBUG
  Serial.print(F(" [VOLTAGE] "));
  Serial.print(voltage);
  
  Serial.print(F(" [PITCH] "));
  Serial.print(yAngle);
  Serial.print(F(" [ROLL] "));
  Serial.print(xAngle);

  Serial.print(F(" [CH1] "));
  Serial.print(ch1);
  Serial.print(F(" [CH2] "));
  Serial.print(ch2);
  Serial.print(F(" [CH3] "));
  Serial.print(ch3);
  Serial.print(F(" [CH4] "));
  Serial.print(ch4);
  Serial.print(F(" [CH5] "));
  Serial.print(ch5);

  Serial.print(F(" [SATS] "));
  Serial.print(fix.satellites);
  Serial.print(F(" [LAT] "));
  Serial.print(fix.latitude());
  Serial.print(F(" [LNG] "));
  Serial.print(fix.longitude());
  Serial.print(F(" [ALT] "));
  Serial.print(fix.altitude());
  Serial.print(F(" [SPEED] "));
  Serial.print(fix.speed_kph());
  Serial.print(F(" [DISTANCE] "));
  Serial.print(distanceToHome);
  Serial.print(F(" [COURSE] "));
  Serial.print(courseChangeNeeded);
  Serial.print(F(" [DIR] "));
  Serial.print(nav_dir);
  Serial.println();
  #endif
}
