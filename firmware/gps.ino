static void GPSisr(uint8_t c) {
  gps.handle(c);
}
void readGPS() {
  if (gps.available()) {
    fix = gps.read();

    if (fix.satellites > 4 && homeLocation.lat() == 0 && homeLocation.lon() == 0) {
      homeLocation = fix.location;
    }

    distanceToHome = fix.location.DistanceKm(homeLocation);
    float courseToDestination = fix.location.BearingToDegrees(homeLocation);
    courseChangeNeeded = (int)(360 + courseToDestination - fix.heading()) % 360;

    if (distanceToHome < 30) {
      // FLIGHT CIRCLE OVER LOCATION
    } else {
      if (courseChangeNeeded >= 345 || courseChangeNeeded < 15) {
        // FLIGHT FORWARD
      }
      else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345) {
        // MOVE LITTLE LEFT
      }
      else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45) {
        // MOVE LITTLE RIGHT
      }
      else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315) {
        // TURN LEFT
      }
      else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105) {
        // TURN RIGHT
      }
      else {
        // TURN AROUND
      }
    }

  }

  if (gps.overrun()) {
    gps.overrun(false);
  }
}
