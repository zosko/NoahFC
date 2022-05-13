static void readGPS(uint8_t c) {
  gps.encode(c);

  int distanceToHome = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), home_lat, home_lng);
  int courseToDestination = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), home_lat, home_lng);
  int courseChangeNeeded = (int)(360 + courseToDestination - gps.course.deg()) % 360;

  Serial.print(F(" [SATS] "));
  Serial.print(gps.satellites.value());
  Serial.print(F(" [SPEED] "));
  Serial.print(gps.speed.kmph());
  Serial.print(F(" [DIS] "));
  Serial.print(distanceToHome);
  Serial.print(F(" [LOC] "));
  Serial.print(gps.location.lat());
  Serial.print(F(", "));
  Serial.print(gps.location.lng());
  Serial.print(F(" [HOME] "));
  Serial.print(home_lat);
  Serial.print(F(", "));
  Serial.print(home_lng);
  Serial.print(F(" [RX]"));
  Serial.print(gps.charsProcessed());
  Serial.print(F(" [NAV] "));

  if (distanceToHome < 30) {
    Serial.print(F("RETURN TO LAND"));
  } else {
    if (courseChangeNeeded >= 345 || courseChangeNeeded < 15) {
      Serial.print(F("FORWARD"));
    }
    else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345) {
      Serial.print(F("LITTLE LEFT"));
    }
    else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45) {
      Serial.print(F("LITTLE RIGHT"));
    }
    else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315) {
      Serial.print(F("TURN LEFT"));
    }
    else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105) {
      Serial.print(F("TURN RIGHT"));
    }
    else {
      Serial.print(F("TURN AROUND"));
    }
  }
  Serial.println();
}

void setHomePosition() {
  if (gps.satellites.value() > 5 &&
      home_lat == 0.0 &&
      home_lng == 0.0) {
    home_lat = gps.location.lat();
    home_lng = gps.location.lng();
  }
}
