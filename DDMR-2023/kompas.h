void nilai_yaws() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // read a packet from FIFO
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    //    y = ypr[0] * 180 / M_PI; //dalam deegre
    theta = ypr[0] * M_PI / 180; //dalam radian
//    theta = -theta;
    //tet untuk nilai akhir sudut;
    avg_delta_tetha = (theta - tet) / 2;
//    Serial.println(theta);
    //Serial.println(y);
    //    lcd.clearDisplay();
    //    lcd.setTextSize(1);
    //    lcd.setTextColor(WHITE);
    //    lcd.setCursor(30, 1);
    //    lcd.print("MPU6050");
    //    lcd.setCursor(5, 3);
    //    lcd.println(theta);
    //    lcd.display();
  }
  //  delay(10);
}
