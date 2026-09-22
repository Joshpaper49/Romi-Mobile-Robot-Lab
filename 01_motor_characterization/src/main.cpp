#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Motors motors;

void delayFunc(int);
void stopFunc();
void forwardFunc();
void reverseFunc();
void indepFunc();

void setup()
{
  Serial.begin(9600);
  // Give us time after startup before anything moves.
  delay(2000);

  // Run both motors forward.
  motors.setSpeeds(100, 100);



  // Run for one second.
  delay(1000);

  // Stop both motors.
  motors.setSpeeds(0, 0);
  
}

void loop()
{


  motors.setSpeeds(0,0);
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

void indepFunc() {
  //drifting to the left
  motors.setSpeeds(100, 200);

    //drifting to the right
  motors.setSpeeds(200, 100);
};

void delayFunc(int input) {
  delay(input * 1000);
};