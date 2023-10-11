void terima_hcsr() {
  getSlaveData(2, 13); //2 = I2C address, 26 = jumlah bytes, karena sudut yaw max 360, maka bytes di-set 3 untuk 3 karakter
  if (received0.length() > 0) {
    Serial.print(hc0);//kiri
    Serial.print(" ");
    Serial.println(hc1);//kanan
    //    Serial.println(received2.toInt());
    //        Serial.println(received.toFloat());
    //  Serial.println(sudut);
    //  Serial.println(received.toFloat());
  }
}


void getSlaveData(int address, int bytes) {
  received0 = "";
  received1 = "";
  //  received2 = "";
  Wire.requestFrom(address, bytes);
  while (Wire.available()) {
    received0 += String(Wire.readStringUntil('#'));
    received1 += String(Wire.readStringUntil('!'));
    //    received2 += String(Wire.readStringUntil('$'));
  }

  //  Serial.println(String(received0) + ";"
  //                 + String(received1) + ";"
  //                 + String(received2));
  //  sudut = received.toFloat();
  hc0 = received0.toInt();
  hc1 = received1.toInt();
  //  hc2 = received2.toInt();
}
