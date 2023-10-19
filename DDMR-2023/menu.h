void awal_tampilan() {
  lcd.clearDisplay();
  lcd.setTextSize(.8);
  lcd.setTextColor(WHITE);
  lcd.setCursor(41, 1);
  lcd.println("DDMR 2023");
  lcd.setTextSize(.5);
  lcd.drawBitmap(55, 10, robot, 20, 20, BLACK, WHITE);
  lcd.display();
  delay(2000);
}

void menu() {
  if (halaman == 1) {
    lcd.clearDisplay();
    lcd.setTextSize(.05);
    lcd.setTextColor(WHITE);
    lcd.setCursor(30, 0);
    lcd.print("DAFTAR MENU");

    if (menuItem == 1) {
      lcd.setCursor(5, 8);
      lcd.setTextColor(WHITE);
      lcd.print("> Obstacle Avoidance");
    } else {
      lcd.setCursor(5, 8);
      lcd.setTextColor(WHITE);
      lcd.print("  Obstacle Avoidance");
    }

    if (menuItem == 2) {
      lcd.setCursor(5, 16);
      lcd.setTextColor(WHITE);
      lcd.print("> Localization");
    } else {
      lcd.setCursor(5, 16);
      lcd.setTextColor(WHITE);
      lcd.print("  Localization");
    }

    if (menuItem == 3) {
      lcd.setCursor(5, 24);
      lcd.setTextColor(WHITE);
      lcd.print("> Line Follower");
    } else {
      lcd.setCursor(5, 24);
      lcd.setTextColor(WHITE);
      lcd.print("  Line Follower");
    }
  }
  lcd.display();
}

void ObstacleAvoidance() {
  if (halaman == 2) {
    //    lcd.clearDisplay();
    //    lcd.setTextSize(1);
    //    lcd.drawBitmap(15, 0, flagracing, 40, 40, BLACK, WHITE);
    //    lcd.setTextSize(2);
    //    lcd.setCursor(50, 18);
    //    lcd.print("START");
    lcd.clearDisplay();
    if (menuObst == 1) {
      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.setTextColor(WHITE);
      lcd.print("> POS_X: ");
      lcd.setCursor(50, 1);
      lcd.println(cntX_obst);
    } else {
      lcd.setCursor(1, 1);
      lcd.setTextColor(WHITE);
      lcd.print("  POS_X: ");
      lcd.setCursor(50, 1);
      lcd.println(cntX_obst);
    }
    if (menuObst == 2) {
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print("> POS_Y: ");
      lcd.setCursor(50, 10);
      lcd.println(cntY_obst);
    } else {
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print("  POS_Y: ");
      lcd.setCursor(50, 10);
      lcd.println(cntY_obst);
    }
    if (menuObst == 3) {
      lcd.setCursor(1, 20);
      lcd.setTextColor(WHITE);
      lcd.print("> Mulai");
      //      lcd.setCursor(50, 20);
      //      lcd.println(cntY);
    } else {
      lcd.setCursor(1, 20);
      lcd.setTextColor(WHITE);
      lcd.print("  Mulai");
      //      lcd.setCursor(50, 20);
      //      lcd.println(cntY);
    }
  }
  lcd.display();
}

void Localization() {
  if (halaman == 3) {
    lcd.clearDisplay();
    if (menuLoc == 1) {
      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.setTextColor(WHITE);
      lcd.print("> POS_X: ");
      lcd.setCursor(50, 1);
      lcd.println(cntX);
    } else {
      lcd.setCursor(1, 1);
      lcd.setTextColor(WHITE);
      lcd.print("  POS_X: ");
      lcd.setCursor(50, 1);
      lcd.println(cntX);
    }
    if (menuLoc == 2) {
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print("> POS_Y: ");
      lcd.setCursor(50, 10);
      lcd.println(cntY);
    } else {
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print("  POS_Y: ");
      lcd.setCursor(50, 10);
      lcd.println(cntY);
    }
    if (menuLoc == 3) {
      lcd.setCursor(1, 20);
      lcd.setTextColor(WHITE);
      lcd.print("> Mulai");
      //      lcd.setCursor(50, 20);
      //      lcd.println(cntY);
    } else {
      lcd.setCursor(1, 20);
      lcd.setTextColor(WHITE);
      lcd.print("  Mulai");
      //      lcd.setCursor(50, 20);
      //      lcd.println(cntY);
    }
  }
  //  Serial.println(String("POSX: ") + cntX + String("POSY: ") + cntY);
  lcd.display();
}

void LineFollower() {
  if (halaman == 4) {
    lcd.clearDisplay();
    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);
    lcd.setCursor(1, 1);
    lcd.print("Posisikan Pada Track");
    if (ir_kanan() == 1 || ir_tengah() || 1 && ir_kiri() || 1) {
      lcd.setTextSize(1.5);
      lcd.setCursor(25, 20);
      lcd.println("GO!");
    }
  }
  lcd.display();
}

/* Saat Push Button Ditekan */
//void saatUpDitekan() {
//  if (statusBtnUp != statusAkhirBtnUp) {
//    if (statusBtnUp == 0) {
//      UP = true;
//    }
//  }
//  statusAkhirBtnUp = statusBtnUp;
//}

void saatOkDitekan() {
  if (statusBtnOk != statusAkhirBtnOk) {
    if (statusBtnOk == 0) {
      OK = true;
    }
  }
  statusAkhirBtnOk = statusBtnOk;
}

void saatDownDitekan() {
  if (statusBtnDown != statusAkhirBtnDown) {
    if (statusBtnDown == 0) {
      DOWN = true;
    }
  }
  statusAkhirBtnDown = statusBtnDown;
}

void saatBackDitekan() {
  if (statusBtnBack != statusAkhirBtnBack) {
    if (statusBtnBack == 0) {
      BACK = true;
    }
  }
  statusAkhirBtnBack = statusBtnBack;
}
/* Saat Push Button Ditekan */
