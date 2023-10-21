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
  /*Program Inti Pergerakan*/
  //////////////////////////////////////////////////////////////////// REAL ///////////////////////////////////////////////////////////////////
  //  uji coba pushbutton
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
  if (halaman == 2 && menuObst == 1 && statusbtnDecr == 0) cntX_obst -= 10;
  else if (halaman == 2 && menuObst == 1 && statusbtnIncr == 0) cntX_obst += 10;
  else if (halaman == 2 && menuObst == 2 && statusbtnDecr == 0) cntY_obst -= 10;
  else if (halaman == 2 && menuObst == 2 && statusbtnIncr == 0) cntY_obst += 10;


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
  //  terima_hcsr();/
  mulai_obst();
  mulai_Loc();
  mulai_LF();

//  nilai_yaws();
  //  get_posisi();
  //  set_point(100, 0);


  //  nilai_yaws();
  //terimaHCSR-04
  //  terima_hcsr();
  /* Program Inti */

  //  // put your main code here, to run repeatedly:
  //  dxl.setGoalVelocity(DXL_ID1, -25, UNIT_RPM);
  //  dxl.setGoalVelocity(DXL_ID2, 25, UNIT_RPM);/
}
