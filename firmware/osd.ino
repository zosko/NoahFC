void setupOSD() {
  osd.init(10);
  osd.setDisplayOffsets(60, 18);
  osd.setBlinkParams(_8fields, _BT_BT);

  osd.activateOSD();
  osd.printMax7456Char(0x01, 0, 1);
  osd.print("Hello world :)", 1, 3);
  osd.print("Current Arduino time :", 1, 4);

  osd.printMax7456Char(0xD1, 9, 6, true);
  osd.print("00'00\"", 10, 6);
  osd.printMax7456Chars(tab, 2, 12, 7);
}
void showOSD_Data() {

}
