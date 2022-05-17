void readPPM() {
  ch1 = ppm.latestValidChannelValue(1, 0);
  ch2 = ppm.latestValidChannelValue(2, 0);
  ch3 = ppm.latestValidChannelValue(3, 0);
  ch4 = ppm.latestValidChannelValue(4, 0);
  ch5 = ppm.latestValidChannelValue(5, 0);

//  Serial.print("[CH1]");
//  Serial.print(ch1);
//  Serial.print(" [CH2] ");
//  Serial.print(ch2);
//  Serial.print(" [CH3] ");
//  Serial.print(ch3);
//  Serial.print(" [CH4] ");
//  Serial.print(ch4);
//  Serial.print(" [CH5] ");
//  Serial.print(ch5);
//  Serial.println();
}
