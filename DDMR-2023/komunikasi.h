void getSlaveData(int address, int bytes) {
  received0 = "";
  received1 = "";
  received2 = "";
  Wire.requestFrom(address, bytes);
  while (Wire.available()) {
    received0 += String(Wire.readStringUntil('#'));
    received1 += String(Wire.readStringUntil('!'));
    received2 += String(Wire.readStringUntil('$'));
  }
  //  Serial.println(received2);
  //  Serial.println(String(received0.toInt()) + ";"
  //                 + String(received1.toInt()) + ";"
  //                 + String(received2.toInt()));
  //  Serial.println(String(received0) + ";"
  //                 + String(received1) + ";"
  //                 + String(received2));

  //  sudut = received.toFloat();
  hc0 = received0.toInt();
  hc1 = received1.toInt();
  hc2 = received2.toInt();
}

void terima_hcsr() {
  getSlaveData(8, 15); //8 = I2C address, 26 = jumlah bytes, karena sudut yaw max 360, maka bytes di-set 3 untuk 3 karakter
  if (received0.length() > 0 || received1.length() > 0 || received2.length() > 0) {
    Serial.println(String("ki:") + hc0
                   + String(" ka:") + hc1
                   + String(" te:") + hc2);
  }

}
