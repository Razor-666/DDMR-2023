/*OpenRB-150 dan Dynamixel*/
#include <Dynamixel2Arduino.h>
//OpenRB does not require the DIR control pin.
#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = -1;

const uint8_t DXL_ID1 = 1; // Motor Kanan
/*NB: Motor kanan ID1 + mutar mundur - mutar kedepan*/
const uint8_t DXL_ID2 = 2; // Motor Kiri
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
/*OpenRB-150 dan Dynamixel*/

void get_posisi() {
  rotation_1 = dxl.getPresentPosition(DXL_ID1);//, UNIT_DEGREE);
  rotation_2 = dxl.getPresentPosition(DXL_ID2);//, UNIT_DEGREE);
  float D_1 = ((rotation_1 - last_rot_1) / 4096) * (3.14 * 6.5); /*2*3,14*0,034=0,2135 -> keliling roda*/
  float D_2 = ((rotation_2 - last_rot_2) / 4096) * (3.14 * 6.5);
  float D_center = (-D_1 + D_2) / 2; //
  //  Serial.println(String("D1: ") + D_1 + String("D2: ") + D_2);
  //  Serial.println(String("D_Center:") + D_center);
  //untuk mendapatkan nilai tengah pada bagian jarak
  //  x = (cos(theta + avg_delta_tetha) * rotation_1) - (cos(theta + avg_delta_tetha) * rotation_2);
  //  y = (sin(theta + avg_delta_tetha) * rotation_1) - (sin(theta + avg_delta_tetha) * rotation_2);
  x = x_last + (D_center * cos(theta + avg_delta_tetha / 2));
  y = y_last + (D_center * sin(theta + avg_delta_tetha / 2));
  //Serial.println(String("X: ") + x + String(" Y: ") + y); //menampilkan koordinat sekarang

  tet = theta;
  x_last = x;
  y_last = y;
  last_rot_1 = rotation_1;
  last_rot_2 = rotation_2;
}

void set_point(float xg, float yg) {

  /* Attractive Potential Fiorce */
  //  Fax = -1 * (x - xg);
  //  Fay = -1 * (y - yg);

  //inti
  delta_x = xg - x;
  delta_y = yg - y;
  //  Serial.println(String("Delta_x: ") + delta_x + String("Delta_y: ") + delta_y);
  //  delta_x = xg - x;
  //  delta_y = yg - y;


  //  Ftx = Fax; //
  //  Fty = Fay;
  /*----------------------------------------*/

  rho = sqrt (pow(delta_x, 2) + pow(delta_y, 2));
  Serial.println(String("rho: ") + rho );

  //Logika obstacle avoidance pengatur sudut //hc0 = ki //hc1 = ka //hc2 = te
  if (halaman == 2) {
    terima_hcsr();

    if (hc0 > 25 && hc2 > 25 && hc1 > 25) { //000
      sdt = atan2(delta_y, delta_x);
    } else if (hc0 > 25 && hc2 > 25 && hc1 <= 25) { //001
      sdt = atan2(delta_y, delta_x) + 6.1;
    } else if (hc0 > 25 && hc2 <= 25 && hc1 > 25) { //010
      sdt = atan2(delta_y, delta_x) + 6.1;
    } else if (hc0 > 25 && hc2 <= 25 && hc1 <= 25) { //011
      sdt = atan2(delta_y, delta_x) + 4.7;
    } else if (hc0 <= 25 && hc2 > 25 && hc1 > 25) { //100
      sdt = atan2(delta_y, delta_x) - 3.14;
    } else if (hc0 <= 25 && hc2 <= 25 && hc1 > 25) { //110
      sdt = atan2(delta_y, delta_x) - 4.7;
    } else if (hc0 <= 25 && hc2 > 25 && hc1 <= 25) { //101
      sdt = atan2(delta_y, delta_x) + 6.1;
    } else {
      sdt = atan2(delta_y, delta_x) + 4.7;
    }
    //    if (hc0 > 15 && hc2 > 15 && hc1 > 15)sdt = atan2(delta_y, delta_x); //000
    //
    //    else if (hc0 > 20 && hc2 > 15 && hc1 < 20)sdt = atan2(delta_y, delta_x) + 1.57; //001
    //
    //    else if (hc0 > 20 && hc2 < 15 && hc1 > 20)sdt = atan2(delta_y, delta_x) - 6.2; //010
    //
    //    else if (hc0 > 20 && hc2 > 15 && hc1 < 20)sdt = atan2(delta_y, delta_x) + 1.57; //011
    //
    //    else if (hc0 < 20 && hc2 > 15 && hc1 > 20)sdt = atan2(delta_y, delta_x) - 6.2; //100
    //
    //    else if (hc0 < 20 && hc2 < 20 && hc1 > 20) sdt = atan2(delta_y, delta_x) - 6.2; //110
    //
    //    else if (hc0 > 20 && hc2 < 15 && hc1 < 20) sdt = atan2(delta_y, delta_x) + 1.57; //101

    //    else sdt = atan2(delta_y, delta_x) + 0.78;
  }
  else if (halaman == 3) sdt = atan2(delta_y, delta_x);
  //Logika obstacle avoidance pengatur sudut //hc0 = ki //hc1 = ka //hc2 = te

  //  Serial.println(String("SDT: ") + sdt);
  //  sdt = atan2(delta_y, delta_x);

  alpha = sdt - theta;
  beta  = -theta - alpha;

  vel   = krho * rho;
  omega = 4 * alpha - 1 * beta;

  vel_r = vel + (omega * 22.5 / 10); //omega*L/(2R) aslinya 0.168 //0.2
  vel_l = vel - (omega * 22.5 / 10);
  //  Serial.println(String("Vel_r: ") + vel_r + ";" + String("Vel_l: ") + vel_l);

  if (vel_r > 50)
  {
    Vr = 50;
  }
  else
  {
    Vr = vel_r;
    if (rho < 5) Vr = 0; //rho diganti ke 5 100cm=1
  }

  if (vel_l > 50)
  {
    Vl = 50;
  }
  else
  {
    Vl = vel_l;
    if (rho < 5) Vl = 0;
  }
  //
  //  //DEBUG_SERIAL.println(delta_x);
  if (rho > 5) //default 0.1
  {
    dxl.setGoalVelocity(DXL_ID1, -Vr, UNIT_RPM);
    dxl.setGoalVelocity(DXL_ID2, Vl, UNIT_RPM);
  }
  else
  {
    dxl.setGoalVelocity(DXL_ID1, 0, UNIT_RPM);
    dxl.setGoalVelocity(DXL_ID2, 0, UNIT_RPM);
  }
  //  Serial.println(String("Vr: ") + Vr + ";" + String("Vl: ") + Vl +  String("Xg: ") + xg +  String("Xy: ") + yg);
}

void mulai_obst() {
  if (halaman == 2 && menuObst == 3 && statusBtnOk == 0) {
    while (true) {
      nilai_yaws();
      get_posisi();
      set_point(cntX_obst, cntY_obst);

      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.println("Koordinat Sekarang");
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print(String("X: ") + x);
      lcd.setCursor(1, 20);
      lcd.print(String("Y: ") + y);

      switch (x == xg && y == yg) {
        case 1:
          break;
      }
      lcd.display();
    }
  }
}

void mulai_Loc() {
  if (halaman == 3 && menuLoc == 3 && statusBtnOk == 0) {
    while (true) {
      //      terima_hcsr();
      nilai_yaws();
      get_posisi();
      set_point(cntX, cntY);

      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.println("Koordinat Sekarang");
      lcd.setCursor(1, 10);
      lcd.setTextColor(WHITE);
      lcd.print(String("X: ") + x);
      lcd.setCursor(1, 20);
      lcd.print(String("Y: ") + y);

      switch (x == xg && y == yg) {
        case 1:
          break;
      }
      Wire.flush();
      lcd.display();
    }
  }
}

int ir_kanan() {
  return digitalRead(pinIr_kanan);
}
int ir_kiri() {
  return digitalRead(pinIr_kiri);
}

int ir_tengah() {
  return digitalRead(pinIr_tengah);
}

void mulai_LF() {
  if (halaman == 4 && statusbtnDecr == 0) {
    lcd.clearDisplay();
    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);
    lcd.drawBitmap(30, 0, flagracing, 40, 40, BLACK, WHITE);
    lcd.display();
    while (true) {
      //Maju
      if (ir_tengah() == 1) {
        dxl.setGoalVelocity(DXL_ID1, -50, UNIT_RPM);
        dxl.setGoalVelocity(DXL_ID2, 50, UNIT_RPM);
      }
      //Kiri
      else if (ir_kanan() == 0 && ir_kiri() == 1 && ir_tengah() == 0) {
        dxl.setGoalVelocity(DXL_ID1, -50, UNIT_RPM); //kanan
        dxl.setGoalVelocity(DXL_ID2, -50, UNIT_RPM); //kiri
      }
      //Kanan
      else if (ir_tengah() == 0 && ir_kanan() == 1 && ir_kiri() == 0) {
        dxl.setGoalVelocity(DXL_ID1, 50, UNIT_RPM); //kanan
        dxl.setGoalVelocity(DXL_ID2, 50, UNIT_RPM); //kiri
      }
      else {
        dxl.setGoalVelocity(DXL_ID1, 0, UNIT_RPM);
        dxl.setGoalVelocity(DXL_ID2, 0, UNIT_RPM);
      }
      switch (ir_tengah() == 0 && ir_kanan() == 0 && ir_kiri() == 0) {
        case 1:
          break;
      }
    }
  }
}
