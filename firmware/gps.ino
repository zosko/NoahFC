static void GPSisr(uint8_t c) {
  gps.handle(c);
}
void readGPS() {
  ledGpsIdle();
  if (gps.available()) {
    ledGpsReceive();
    fix = gps.read();

    if (fix.satellites > 5 && homeLocation.lat() == 0 && homeLocation.lon() == 0) {
      homeLocation = fix.location;
    }

    float distanceToHome = fix.location.DistanceKm(homeLocation);
    float courseToDestination = fix.location.BearingToDegrees(homeLocation);
    int courseChangeNeeded = (int)(360 + courseToDestination - fix.heading()) % 360;

    if (distanceToHome < 30.0) {
      navigation = ARRIVED;
    } else {
      if (courseChangeNeeded >= 345 || courseChangeNeeded < 15) {
        navigation = FORWARD;
      }
      else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345) {
        navigation = TURN_LITTLE_LEFT;
      }
      else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45) {
        navigation = TURN_LITTLE_RIGHT;
      }
      else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315) {
        navigation = TURN_LEFT;
      }
      else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105) {
        navigation = TURN_RIGHT;
      }
      else {
        navigation = TURN_AROUND;
      }
    }

  }

  if (gps.overrun()) {
    gps.overrun(false);
  }
}
