static void GPSisr(uint8_t c) {
  gps.handle(c);
}
void readGPS() {
  if (gps.available()) {
    fix = gps.read();

    if (fix.satellites > 4 && homeLocation.lat() == 0 && homeLocation.lon() == 0) {
      homeLocation = fix.location;
    }

    float distanceToHome = fix.location.DistanceKm(homeLocation);
    float courseToDestination = fix.location.BearingToDegrees(homeLocation);
    int courseChangeNeeded = (int)(360 + courseToDestination - fix.heading()) % 360;

//    Serial.print(F(" [SATS] "));
//    Serial.print(fix.satellites);
//    Serial.print(F(" [LAT] "));
//    Serial.print(fix.latitude());
//    Serial.print(F(" [LNG] "));
//    Serial.print(fix.longitude());
//    Serial.print(F(" [ALT] "));
//    Serial.print(fix.altitude());
//    Serial.print(F(" [SPEED] "));
//    Serial.print(fix.speed_kph());
//    Serial.print(F(" [DISTANCE] "));
//    Serial.print(distanceToHome);
//    Serial.print(F(" [DIR] "));

    if (distanceToHome < 30) {
//      Serial.print(F("RETURN TO LAND"));
    } else {
      if (courseChangeNeeded >= 345 || courseChangeNeeded < 15) {
//        Serial.print(F("FORWARD"));
      }
      else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345) {
//        Serial.print(F("LITTLE LEFT"));
      }
      else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45) {
//        Serial.print(F("LITTLE RIGHT"));
      }
      else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315) {
//        Serial.print(F("TURN LEFT"));
      }
      else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105) {
//        Serial.print(F("TURN RIGHT"));
      }
      else {
//        Serial.print(F("TURN AROUND"));
      }
    }
//    Serial.println();
  }

  if (gps.overrun()) {
    gps.overrun(false);
//    Serial.println(F("DATA OVERRUN: took too long to print GPS data!") );
  }
}
