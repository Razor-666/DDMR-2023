/* Kinematic Dynamixel */
double rotation_1 = 0;
double rotation_2 = 0;
double x_last = 0;
double y_last = 0;
double xg; //orientasi x
double yg; //orientasi y
double krho = 0.2; //gain
double Vr, Vl, vel_r, vel_l;
float last_rot_1 = 0;
float last_rot_2 = 0;
float x, y;
double delta_x, delta_y, rho, alpha, sdt, beta, vel, omega, Fax, Fay, Ftx, Fty;
/* Kinematic Dynamixel */

/* Kompas */
float theta = 0.00;
float tet = 0.00;
float avg_delta_tetha = 0.00;
/* Kompas */

/*MPU 6050*/
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 mpu(0x68, &Wire);
#define INTERRUPT_PIN 2
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}
//int y;
//int countY;
//int k, y, yfrist, ysecond, plus;
//int yaws;
//int yaw;
//bool start;
//int limit;
//float vol;
//int waktu = 0;

void (* reset) (void) = 0;
/*MPU 6050*/

/*OLED*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
/*OLED*/

/* HCSR-04 */
//#define echoPin1 4 //Echo Pin Kiri
//#define trigPin1 5 //Trigger Pin Kiri

//const int echoPin2 = 8; //Echo Pin Tengah
//const int trigPin2 = 7; //Trigger Pin Tengah

//#define echoPin3 0 //Echo Pin Kanan
//#define trigPin3 1 //Trigger Pin Kanan

//int maximumRange1 = 200; //kebutuhan akan maksimal range
//int minimumRange1 = 00; //kebutuhan akan minimal range
//int maximumRange2 = 200; //kebutuhan akan maksimal range
//int minimumRange2 = 00; //kebutuhan akan minimal range
//int maximumRange3 = 200; //kebutuhan akan maksimal range
//int minimumRange3 = 00; //kebutuhan akan minimal range
//long duration1, duration2, duration3, ki, te, ka; //waktu untuk kalkulasi jarak
/* HCSR-04 */

/*Menu Tampilan*/
int halaman = 1;
int menuItem = 1;
int cntX = 0;
int cntY = 0;
int cntX_obst = 0;
int cntY_obst = 0;
int menuLoc = 1;
int menuObst = 1;

#define btnDown 6 //pushbutton diganti
//#define btnUp 9
#define btnOk   7
#define btnBack 8

int btnIncr = 9;
int btnDecr = 10;
int statusbtnIncr, statusbtnDecr;

//boolean statusBtnUp   = false;
boolean statusBtnOk   = false;
boolean statusBtnDown = false;
boolean statusBtnBack = false;

//boolean statusAkhirBtnUp   = false;/
boolean statusAkhirBtnOk   = false;
boolean statusAkhirBtnDown = false;
boolean statusAkhirBtnBack = false;

//boolean UP   = false;/
boolean OK   = false;
boolean DOWN = false;
boolean BACK = false;
/*Menu Tampilan*/

/*ICON Tampilan OLED*/
const unsigned char robot [] PROGMEM = {
  0xff, 0xff, 0xf0, 0xff, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x9f, 0xf0, 0xff, 0x9f, 0xf0, 0xff,
  0x9f, 0xf0, 0xe0, 0x00, 0x70, 0xcf, 0xff, 0x30, 0x1f, 0xff, 0x80, 0x18, 0xf1, 0x80, 0x58, 0xf1,
  0xa0, 0x59, 0xf9, 0xa0, 0x5f, 0xff, 0xa0, 0x5f, 0xff, 0xa0, 0x5c, 0x03, 0xa0, 0x1c, 0x03, 0x80,
  0x9e, 0x07, 0x90, 0xcf, 0xff, 0x30, 0xe0, 0x00, 0x70, 0xff, 0xff, 0xf0
};

const unsigned char flagracing [] PROGMEM = {
  0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xf8, 0x79, 0xff, 0xff,
  0xff, 0xe0, 0x79, 0xff, 0xff, 0xff, 0x80, 0x7c, 0xff, 0xff, 0xfe, 0x10, 0x7c, 0xff, 0xfc, 0x80,
  0x78, 0x00, 0xff, 0xf8, 0x80, 0xf8, 0xc0, 0xff, 0xfc, 0x80, 0xfb, 0xc0, 0x7f, 0xfc, 0x40, 0xf7,
  0xc0, 0x7f, 0xfc, 0x40, 0x63, 0xe2, 0x7f, 0xfc, 0x40, 0x83, 0xde, 0x7f, 0xfe, 0x47, 0x83, 0x1f,
  0x3f, 0xfe, 0x27, 0xc0, 0x1f, 0x3f, 0xfe, 0x27, 0xc6, 0x0e, 0x3f, 0xfe, 0x27, 0xde, 0x00, 0x1f,
  0xff, 0x33, 0x3e, 0x00, 0xff, 0xff, 0x10, 0x1e, 0x0f, 0xff, 0xff, 0x10, 0x1c, 0x3f, 0xff, 0xff,
  0x90, 0x10, 0xff, 0xff, 0xff, 0x98, 0x03, 0xff, 0xff, 0xff, 0x88, 0x0f, 0xff, 0xff, 0xff, 0x8c,
  0x7f, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff,
  0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff,
  0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff,
  0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff,
  0xf9, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff
};
/*ICON Tampilan OLED*/

/* IR PIN */
int pinIr_kiri = 5;
int pinIr_kanan = 4;
int pinIr_tengah = 3;
/* IR PIN */

/* OpenRB Master */
//#include <Wire.h>
String received0 = "";
String received1 = "";
String received2 = "";
int hc0, hc1, hc2;
/* OpenRB Master */

void inisial() {
  /* OpenRB Master */
  Wire.begin();
  Serial.begin(9600);
  /* OpenRB Master */

  /*MPU6050*/
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    mpu.setDMPEnabled(true);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;

    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    reset();
  }

  lcd.begin(SSD1306_SWITCHCAPVCC, 0X3C);

  /* Bagian PinMode */
  //button
  //  pinMode(btnUp,   INPUT_PULLUP);
  pinMode(btnOk,   INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);

  pinMode(btnIncr, INPUT_PULLUP);
  pinMode(btnDecr, INPUT_PULLUP);

  pinMode(pinIr_kanan, INPUT);
  pinMode(pinIr_kiri, INPUT);
  /* Bagian PinMode */
}
