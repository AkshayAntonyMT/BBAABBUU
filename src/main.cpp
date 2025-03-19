#include "BluetoothSerial.h"
#include <Arduino.h>
BluetoothSerial serialBT;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed
int Speed = 150;

//declare channel for pwm Output
#define R 0
#define L 1

//PWM Pin for Controlling the speed
int enA = 13;
int enB = 25;

//motor controlling pin
int IN1 = 12;
int IN2 = 14;
int IN3 = 27;
int IN4 = 26;

void backward();
void forward();
void right();
void left();
void stop();

void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("BABu");

  //output pin declare
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup PWM channels
  ledcSetup(R, 5000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enA, R);
  ledcSetup(L, 5000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enB, L);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Intial State of Car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {

  while (serialBT.available()) {
    btSignal = serialBT.read();
    //Serial.println(btSignal);

    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

//to see the incoming signal in serial monitor
    Serial.println(btSignal);
    
  //backward
    if (btSignal == 'B') {
      backward();
    }

  //forward
    else if (btSignal == 'F') {
      forward();
    }

  //LEFT
    else if (btSignal == 'L') {
      left();
    }

  //RIGHT
    else if (btSignal == 'R') {
      right();
    }

  //STOP
    else if (btSignal == 'S') {
      stop();
    }
  }
}


//function for control motor
void left() {
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }

void right() {
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward() {
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
    ledcWrite(R, Speed);
    ledcWrite(L, Speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
