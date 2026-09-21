#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Motors motors;

void setup()
{
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
}