#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Encoders encoders;
Romi32U4Motors motors;

double counts_per_rev{1440.0};
double circumference{7.0}; // cm * PI
double desired_heading{90};
double current_heading{0};
double track_width{14.1};

struct movementPair
{
  int desired_distance{};
  int degree{};
  bool is_linear{};
};

movementPair move_array[4]{
    {30, 0, true},
    {0, 90, false},
    {0, -90, false},
    {-30, 0, true}};

bool driveTo(movementPair value, double center_dist, double degree);

void setup()
{
  Serial.begin(9600);

  delay(15000);
}

void loop()
{

  static size_t current_index = 0;

  const size_t move_size = (sizeof(move_array) / sizeof(move_array[0]));

  if (current_index >= move_size)
  {
    motors.setSpeeds(0, 0);
    return;
  }

  int32_t left_counts = encoders.getCountsLeft();
  int32_t right_counts = encoders.getCountsRight();

  double left_distance = (left_counts / counts_per_rev) * circumference * PI;
  double right_distance = (right_counts / counts_per_rev) * circumference * PI;

  double center_distance = (left_distance + right_distance) / 2.0;

  double current_heading = ((right_distance - left_distance) / track_width) * (180 / PI);

  bool result = driveTo(move_array[current_index], center_distance, current_heading);

  if (result)
  {
    motors.setSpeeds(0, 0);
    delay(5000);
    current_index++;
  }
}

bool driveTo(movementPair value, double center_dist, double degree)
{
  int motor_speed{100};
  int sign_dist = (value.desired_distance < 0) ? -1 : 1;
  int sign_deg = (value.degree < 0) ? -1 : 1;

  if (value.is_linear)
  {
    motor_speed *= sign_dist;
    motors.setSpeeds(motor_speed, motor_speed);

    bool finished = (sign_dist > 0) ? (center_dist >= value.desired_distance) : (center_dist <= value.desired_distance);

    if (finished)
    {
      motors.setSpeeds(0, 0);
      encoders.getCountsAndResetLeft();
      encoders.getCountsAndResetRight();
      return true;
    }
  }
  else
  {

    sign_deg > 0 ? motors.setSpeeds(-motor_speed, motor_speed) : motors.setSpeeds(motor_speed, -motor_speed);
    bool finished = sign_deg > 0 ? (degree >= value.degree) : (degree <= value.degree);

    if (finished)
    {
      motors.setSpeeds(0, 0);
      encoders.getCountsAndResetLeft();
      encoders.getCountsAndResetRight();
      return true;
    }
  }
  return false;
}
