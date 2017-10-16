/*
 <^/M! (FL)       \^> M2 (FR)
   ----------------
  |                |
  |                |
  |                |
  |                |
  |                |
   ----------------
 <v\M3 (BL)       /v> M4 (BR)
 */

#include <SPI.h>
#include <PS3BT.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

int Led = 13;
int x1, x2, y1, y2, p1, p2, p3, p4, s;
int m11 = 3; //FL
int m12 = 4;
int m21 = 5; //FR
int m22 = 6;
int m31 = 7; //BL
int m32 = 8;
int m41 = 9; //BR
int m42 = 10;

void setup() {

   Serial.begin(115200);

   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }

  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  pinMode(m11, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m42, OUTPUT);
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m31, LOW);
  digitalWrite(m32, LOW);
  digitalWrite(m41, LOW);
  digitalWrite(m42, LOW);

}

void loop() {

  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    //Taking Analog input from joystick
    x1 =  map(PS3.getAnalogHat(RightHatX), 0, 255, -122, 123);
    y1 =  map(PS3.getAnalogHat(RightHatY), 0, 255, -122, 123);
    x2 =  map(PS3.getAnalogHat(LeftHatX), 0, 255, -122, 123);
    y2 =  map(PS3.getAnalogHat(LeftHatY), 0, 255, -122, 123);
    //Projections on motor lines
    s = sqrt(2);
    p1 = -x1+y1/s;
    p2 = x1+y1/s;
    p3 = x1-y1/s;
    p4 = -x1-y1/s;
    //Printing all values
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(x2);
    Serial.println(y2);
    Serial.println(p1);
    Serial.println(p2);
    Serial.println(p3);
    Serial.println(p4); 

    if (p1>0) {
      Serial.println("I");
      p1 = map(p1, 0, 173, 0, 255);
      analogWrite(m11, p1);
      analogWrite(m12, 0);
    }
    else {
      Serial.println("II");
      p1 = map(p1, -173, 0, 255, 0);
      analogWrite(m11, 0);
      analogWrite(m12, p1);
    }
    if (p2>0) {
      Serial.println("III");
      p2 = map(p2, 0, 173, 0, 255);
      analogWrite(m21, p2);
      analogWrite(m22, 0);
    }
    else {
      Serial.println("IV");
      p2 = map(p2, -173, 0, 255, 0);
      analogWrite(m21, 0);
      analogWrite(m22, p2);
    }
    if (p3>0) {
      Serial.println("V");
      p3 = map(p3, 0, 173, 0, 255);
      analogWrite(m31, p3);
      analogWrite(m32, 0);
    }
    else {
      Serial.println("VI");
      p3 = map(p3, -173, 0, 255, 0);
      analogWrite(m31, 0);
      analogWrite(m32, p3);
    }
    if (p4>0) {
      Serial.println("VII");
      p4 = map(p4, 0, 173, 0, 255);
      analogWrite(m41, p4);
      analogWrite(m42, 0);
    }
    else {
      Serial.println("VIII");
      p4 = map(p4, -173, 0, 255, 0);
      analogWrite(m41, 0);
      analogWrite(m42, p4);
    }


  if (PS3.getButtonClick(UP)) {

    digitalWrite(Led, HIGH);
    Serial.print(F("\r\nUp"));

     if (PS3.PS3Connected) {
      PS3.setLedOff();
      PS3.setLedOn(LED1);
    }

  }

}

  Serial.println("------------"); 
}

