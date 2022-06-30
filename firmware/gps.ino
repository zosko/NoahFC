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

    distanceToHome = fix.location.DistanceKm(homeLocation);
    float courseToDestination = fix.location.BearingToDegrees(homeLocation);
    courseChangeNeeded = (int)(360 + courseToDestination - fix.heading()) % 360;

    if (distanceToHome < 30) { // FLIGHT CIRCLE OVER LOCATION
      nav_dir = '@';
    } else {
      if (courseChangeNeeded >= 345 || courseChangeNeeded < 15) { // FLIGHT FORWARD
        nav_dir = '^';
      }
      else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345) { // MOVE LITTLE LEFT
        nav_dir = '{';
      }
      else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45) { // MOVE LITTLE RIGHT
        nav_dir = '}';
      }
      else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315) { // TURN LEFT
        nav_dir = '<';
      }
      else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105) { // TURN RIGHT
        nav_dir = '>';
      }
      else { // TURN AROUND
        nav_dir = '&';
      }
    }

  }

  if (gps.overrun()) {
    gps.overrun(false);
  }
}
