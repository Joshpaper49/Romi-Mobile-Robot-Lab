#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Motors motors;

void delayFunc(int);
void stopFunc();
void forwardFunc();
void reverseFunc();
void indepFunc(bool left);
void rotateFunc();

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  //forward section
  forwardFunc();
  delayFunc(5);
  stopFunc();

  //reverse section
  reverseFunc();
  delayFunc(5);
  stopFunc();

  //left forward section
  indepFunc(true);
  delayFunc(5);
  stopFunc();

  //right forward section
  indepFunc(false);
  delayFunc(5);
  stopFunc();

  //rotate section
  rotateFunc();
  delayFunc(5);
  stopFunc();

  delayFunc(7);
}


void stopFunc() {
  motors.setSpeeds(0,0);
};

void forwardFunc() {
  motors.setSpeeds(250, 250);
};

void reverseFunc() {
  motors.setSpeeds(-250, -250);  
};

void indepFunc(bool left) {
    left ? motors.setSpeeds(100, 200) : motors.setSpeeds(200, 100);
};

void delayFunc(int input) {
  delay(input * 1000);
};

void rotateFunc() {
  motors.setSpeeds(100, -100);
};