#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4Encoders encoders;

  double wheel_diameter {7.0};
  double counts_per_rev {1440.0};


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting!!");
  delay(15000);

}

void loop()
{
  // put your main code here, to run repeatedly:
  int32_t left_counts {};
  int32_t right_counts {};

  left_counts = encoders.getCountsAndResetLeft();
  right_counts = encoders.getCountsAndResetRight();

  motors.setSpeeds(100, 100);  
  delay(1500);
  
  left_counts = encoders.getCountsLeft();
  right_counts = encoders.getCountsRight();  

  motors.setSpeeds(0,0);  

  double left_distance = (left_counts/counts_per_rev) * wheel_diameter * PI;
  double right_distance = (right_counts/counts_per_rev) * wheel_diameter * PI;

  Serial.print("Left distance: ");
  Serial.print(left_distance);
  Serial.println(" cm");

  Serial.print("Right distance: ");
  Serial.print(right_distance);
  Serial.println(" cm");

  delay(10000);

}
