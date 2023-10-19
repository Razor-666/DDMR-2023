#include <Wire.h>

const int trigPin[] = {8, 3}; //knan 3//4
const int echoPin[] = {9, 4}; //kiri 8//9
long duration[5];
int distance[5];

void setup() {
  Wire.begin(8); //I2C address
  Wire.onRequest(requestEvent);

  //      Serial.begin(9600);
  pinMode(trigPin[0], OUTPUT);
  pinMode(echoPin[0], INPUT);

  pinMode(trigPin[1], OUTPUT);
  pinMode(echoPin[1], INPUT);
  //
  //  pinMode(trigPin[2], OUTPUT);
  //  pinMode(echoPin[2], INPUT);
}

void loop() {
  digitalWrite(trigPin[0], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[0], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[0], LOW);
  duration[0] = pulseIn(echoPin[0], HIGH);
  distance[0] = duration[0] * 0.034 / 2;
  //Serial.print(String(distance[0]) + "#");

  digitalWrite(trigPin[1], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[1], LOW);
  duration[1] = pulseIn(echoPin[1], HIGH);
  distance[1] = duration[1] * 0.034 / 2;
  //  //Serial.print(String(distance[1]) + "!");
  //
  //  digitalWrite(trigPin[2], LOW);
  //  delayMicroseconds(2);
  //  digitalWrite(trigPin[2], HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(trigPin[2], LOW);
  //  duration[2] = pulseIn(echoPin[2], HIGH);
  //  distance[2] = duration[2] * 0.034 / 2;

  //  Serial.println(String(distance[0]) + "#" +
  //                 String(distance[1]) + "!" +
  //                 String(distance[2]) + "$" );
  //Serial.println(String(distance[0]));

  delay(50);
}

void requestEvent() {
  //  String hc0 = String("Dist0:") + distance[0] + "#";
  String hc0 = String(distance[0]) + "#";
  Wire.write(hc0.c_str()); //kiri
  //  String hc1 = String("Dist1: ") + distance[1] + "!";
  String hc1 = String(distance[1]) + "!";
  Wire.write(hc1.c_str()); //kanan
  //  String hc2 = String("Dist2: ") + distance[2] + "$";
  //  Wire.write(hc2.c_str());
}
