#include <Arduino.h>
#include <Romi32U4.h>

Romi32U4Encoders encoders;
Romi32U4Motors motors;

double counts_per_rev{1440.0};
double circumference{7.0}; // cm * PI
double track_width{14.1};

struct destData
{
  int desired_distance{};
  int degree{};
};

struct odomInfo
{
  double center_distance{};
  double current_heading{};
};

struct motor_effort
{
  int left_effort{};
  int right_effort{};
};

destData move_array[4]{
    // linear_distance, degree
    {10, 45},
    {-10, -45},
    {10, 45},
    {-10, -45}};

odomInfo odomCalc();
motor_effort effortCalc(odomInfo data, destData destination);
int deadbandCompensation(double effort);
bool driveTo(destData destination);

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

    static bool completion_printed = false;
    motors.setSpeeds(0, 0);

    if(!completion_printed) {
      Serial.println("Done!"); 
      completion_printed = true;
    }
       
    return;
  }

  if (driveTo(move_array[current_index]))
  {
    motors.setSpeeds(0, 0);
    delay(5000);
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    current_index++;
  }
}

odomInfo odomCalc()
{

  int32_t left_counts = encoders.getCountsLeft();
  int32_t right_counts = encoders.getCountsRight();

  double left_distance = (left_counts / counts_per_rev) * circumference * PI;
  double right_distance = (right_counts / counts_per_rev) * circumference * PI;

  double center_distance = (left_distance + right_distance) / 2.0;

  double current_heading = ((right_distance - left_distance) / track_width) * (180 / PI);

  odomInfo result{center_distance, current_heading};

  return result;
}

motor_effort effortCalc(odomInfo data, destData destination)
{
  double Kp_dist = 5.0;
  double Kp_degree = 2.0;

  double dist_err = destination.desired_distance - data.center_distance;
  double heading_err = (destination.degree - data.current_heading);

  int left_effort = deadbandCompensation(Kp_dist * dist_err - Kp_degree * heading_err);
  int right_effort = deadbandCompensation(Kp_dist * dist_err + Kp_degree * heading_err);

  motor_effort result = {left_effort, right_effort};

  return result;
}

int deadbandCompensation(double effort) {

  const double min_effort = 40.0;
  const double max_effort = 300.0;

  effort = constrain(effort, -max_effort, max_effort);

  if(effort == 0) 
    return 0;

  double magnitude = fabs(effort);

  double op_effort = min_effort + (max_effort - min_effort) * (magnitude/max_effort);

  return (effort > 0) ? static_cast<int>(op_effort) : -static_cast<int>(op_effort);
}

bool driveTo(destData value)
{

  odomInfo update = odomCalc();

  if (fabs((value.desired_distance - update.center_distance)) <= 0.5 && fabs((value.degree - update.current_heading)) <= 2.0)
  {
    motors.setSpeeds(0, 0);
    return true;
  }

  motor_effort result = effortCalc(update, value);
  motors.setSpeeds(result.left_effort, result.right_effort);

  return false;
}
