#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Encoders encoders;
Romi32U4Motors motors;

double counts_per_rev {1440.0};
double circumference {7.0}; // cm * PI
double desired_heading {90};
double current_heading{0};
double track_width{14.1};

void setup() {
Serial.begin(9600);

delay(7000);


}

void loop() {

  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();


  while(current_heading < desired_heading) {
    motors.setSpeeds(-100, 100);

    int32_t left_counts = encoders.getCountsLeft();
    int32_t right_counts = encoders.getCountsRight();

    double left_distance = (left_counts/counts_per_rev) * circumference * PI;
    double right_distance = (right_counts/counts_per_rev) * circumference * PI;
    
    current_heading = ((right_distance - left_distance) / track_width) * (180/PI);

    Serial.print("current heading: ");
    Serial.println(current_heading);
  }

  motors.setSpeeds(0,0);

}
