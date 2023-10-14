/* Project by Razor-666 */
/* 2023 */
#include "hardware.h"
#include "kompas.h"
#include "komunikasi.h"
#include "DDMR.h"
#include "menu.h"

void setup() {
  inisial();

  awal_tampilan();
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID1);
  dxl.ping(DXL_ID2);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID1);
  dxl.setOperatingMode(DXL_ID1, OP_VELOCITY);
  dxl.torqueOn(DXL_ID1);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_VELOCITY);
  dxl.torqueOn(DXL_ID2);
}

void loop() {
  /* Program Inti*/

  //  nilai_yaws();
  //  get_posisi();
  //  set_point(150.0, 0.0);
  //
  //  tet = theta;
  //  x_last = x;
  //  y_last = y;
  //  last_rot_1 = rotation_1;
  //  last_rot_2 = rotation_2;
  /* Program Inti*/

  /*Program Inti Pergerakan*/
  //nilai_yaws();

  //  rotation_1 = dxl.getPresentPosition(DXL_ID1);//, UNIT_DEGREE);
  //  rotation_2 = dxl.getPresentPosition(DXL_ID2);//, UNIT_DEGREE);
  //
  //  float D_1 = ((rotation_1 - last_rot_1) / 4096) * 21.35; /*2*3,14*0,034=0,2135 -> keliling roda*/
  //  float D_2 = ((rotation_2 - last_rot_2) / 4096) * 21.35;
  //  //
  //  float D_center = (-D_1 + D_2) / 2;
  //  //
  //  //untuk mendapatkan nilai tengah pada bagian jarak
  //  x = x_last + (D_center * cos(theta + avg_delta_tetha / 2));
  //  y = y_last + (D_center * sin(theta + avg_delta_tetha / 2));
  //  //  Serial.println(String("X: ") + x + String("Y: ") + y);
  //
  //    //  //HCSR04
  //    digitalWrite(trigPin1, LOW); delayMicroseconds(2);
  //    digitalWrite(trigPin1, HIGH); delayMicroseconds(10);
  //    digitalWrite(trigPin1, LOW);
  //    duration1 = pulseIn(echoPin1, HIGH);
  //
  //    digitalWrite(trigPin2, LOW); delayMicroseconds(2);
  //    digitalWrite(trigPin2, HIGH); delayMicroseconds(10);
  //    digitalWrite(trigPin2, LOW);
  //    duration2 = pulseIn(echoPin2, HIGH);
  //
  //    digitalWrite(trigPin3, LOW); delayMicroseconds(2);
  //    digitalWrite(trigPin3, HIGH); delayMicroseconds(10);
  //    digitalWrite(trigPin3, LOW);
  //    duration3 = pulseIn(echoPin3, HIGH);
  //
  //    //perhitungan untuk dijadikan jarak
  //    ki = duration1 / 58.2;
  //    te = duration2 / 58.2;
  //    ka = duration3 / 58.2;


  // Serial.println(ki);
  // Serial.println(te);
  // Serial.println(ka);
  //
  //
  //  //-----------------------
  //  // Kinematic of DDMR
  //  //-----------------------
  //
  //  double delta_x, delta_y, rho, alpha, sdt, beta, vel, omega, Fax, Fay, Ftx, Fty;
  //
  //  /* Attractive Potential Fiorce */
  //  //  Fax = -1 * (x - xg);
  //  //  Fay = -1 * (y - yg);
  //
  //  //inti
  //  delta_x = xg - x;
  //  delta_y = yg - y;
  //  //Serial.println(String("Delta_x: ") + delta_x + String("Delta_y: ") + delta_y);
  //  //  delta_x = xg - x;
  //  //  delta_y = yg - y;
  //
  //
  //  //  Ftx = Fax; //
  //  //  Fty = Fay;
  //  /*----------------------------------------*/
  //
  //  rho = sqrt (pow(delta_x, 2) + pow(delta_y, 2));
  //  Serial.println(String("rho: ") + rho );
  //
  //  //Logika obstacle avoidance pengatur sudut
  //  //  if (ki > 25 && te > 25 && ka > 25) { //000
  //  //    sdt = atan2(Fty, Ftx);
  //  //  } else if (ki > 25 && te > 25 && ka <= 25) { //001
  //  //    sdt = atan2(Fty, Ftx) + 45;
  //  //  } else if (ki > 25 && te <= 25 && ka > 25) { //010
  //  //    sdt = atan2(Fty, Ftx) + 45;
  //  //  } else if (ki > 25 && te <= 25 && ka <= 25) { //011
  //  //    sdt = atan2(Fty, Ftx) + 90;
  //  //  } else if (ki <= 25 && te > 25 && ka > 25) { //100
  //  //    sdt = atan2(Fty, Ftx) - 45;
  //  //  } else if (ki <= 25 && te <= 25 && ka > 25) { //110
  //  //    sdt = atan2(Fty, Ftx) - 90;
  //  //  } else if (ki <= 25 && te > 25 && ka <= 25) { //101
  //  //    sdt = atan2(Fty, Ftx) + 45;
  //  //  } else {
  //  //    sdt = atan2(Fty, Ftx) + 90;
  //  //  }
  //  sdt = atan2(delta_y, delta_x);
  //
  //  alpha = sdt - theta;
  //  beta  = -theta - alpha;
  //
  //  vel   = krho * rho;
  //  omega = 4 * alpha - 1 * beta;
  //
  //  vel_r = vel + (omega * 0.168 / 0.2); //omega*L/(2R) aslinya 0.168
  //  vel_l = vel - (omega * 0.168 / 0.2);
  //  Serial.println(String("Vel_r: ") + vel_r + ";" + String("Vel_l: ") + vel_l);
  //
  //  if (vel_r > 50)
  //  {
  //    Vr = 50;
  //  }
  //  else
  //  {
  //    Vr = vel_r;
  //    if (rho < 0.5) Vr = 0;
  //  }
  //
  //  if (vel_l > 50)
  //  {
  //    Vl = 50;
  //  }
  //  else
  //  {
  //    Vl = vel_l;
  //    if (rho < 0.5) Vl = 0;
  //  }
  //  //
  //  //  //DEBUG_SERIAL.println(delta_x);
  //  if (rho > 0.1)
  //  {
  //    dxl.setGoalVelocity(DXL_ID1, -Vr, UNIT_RPM);
  //    dxl.setGoalVelocity(DXL_ID2, Vl, UNIT_RPM);
  //  }
  //  else
  //  {
  //    dxl.setGoalVelocity(DXL_ID1, Vr, UNIT_RPM);
  //    dxl.setGoalVelocity(DXL_ID2, Vl, UNIT_RPM);
  //  }
  //  Serial.println(String("Vr: ") + Vr + ";" + String("Vl: ") + Vl);
  //
  //  tet = theta;
  //  x_last = x;
  //  y_last = y;
  //  last_rot_1 = rotation_1;
  //  last_rot_2 = rotation_2;

  //////////////////////////////////////////////////////////////////// REAL ///////////////////////////////////////////////////////////////////
  //uji coba pushbutton
  menu();
  ObstacleAvoidance();
  Localization();
  LineFollower();

  ///  statusBtnUp   = digitalRead(btnUp);
  statusBtnOk   = digitalRead(btnOk);
  statusBtnDown = digitalRead(btnDown);
  statusBtnBack = digitalRead(btnBack);

  statusbtnIncr = digitalRead(btnIncr);
  statusbtnDecr = digitalRead(btnDecr);

  //Pemilihan Menu Awal dengan mode PULLUP
  //    saatUpDitekan();
  saatOkDitekan();
  saatDownDitekan();
  saatBackDitekan();

  //  //untuk button down Hal 1
  if (DOWN && halaman == 1) {
    DOWN = false;
    menuItem++;
    if (menuItem > 3)menuItem = 1;
  }
  //  //untuk button down Hal 2
  else if (DOWN && halaman == 2) {
    DOWN = false;
    menuObst++;
    if (menuObst > 3)menuObst = 1;
  }
  //  //untuk button down Hal 3
  else if (DOWN && halaman == 3) {
    DOWN = false;
    menuLoc++;
    if (menuLoc > 3)menuLoc = 1;
  }


  //Untuk push button incr dan decr hal 3
  if (halaman == 3 && menuLoc == 1 && statusbtnDecr == 0) cntX -= 10;
  else if (halaman == 3 && menuLoc == 1 && statusbtnIncr == 0) cntX += 10;
  else if (halaman == 3 && menuLoc == 2 && statusbtnDecr == 0) cntY -= 10;
  else if (halaman == 3 && menuLoc == 2 && statusbtnIncr == 0) cntY += 10;

  //Untuk push button incr dan decr hal 2
  if (halaman == 2 && menuObst == 1 && statusbtnDecr == 0) cntX -= 10;
  else if (halaman == 2 && menuObst == 1 && statusbtnIncr == 0) cntX += 10;
  else if (halaman == 2 && menuObst == 2 && statusbtnDecr == 0) cntY -= 10;
  else if (halaman == 2 && menuObst == 2 && statusbtnIncr == 0) cntY += 10;


  // untuk button ok
  if (OK) {
    OK = false;
    if (halaman == 1 && menuItem == 1) {
      halaman = 2;
    } else if (halaman == 1 && menuItem == 2) {
      halaman = 3;
    } else if (halaman == 1 && menuItem == 3) {
      halaman = 4;
    }
  }
  //
  //  //  untuk button back
  if (BACK) {
    BACK = false;
    if (halaman == 2 || halaman == 3 || halaman == 4 || halaman == 5) {
      halaman = 1;
    }
  }


  //  /* Program Inti */
  //  mulai_Loc();
  //  mulai_LF();

  //terimaHCSR-04
  //    terima_hcsr();

  /* Program Inti */

  //  // put your main code here, to run repeatedly:
  //  dxl.setGoalVelocity(DXL_ID1, -25, UNIT_RPM);
  //  dxl.setGoalVelocity(DXL_ID2, 25, UNIT_RPM);/
}
