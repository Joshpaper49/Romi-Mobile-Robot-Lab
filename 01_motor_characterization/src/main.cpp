#include <Arduino.h>
#include <Romi32U4.h>


Romi32U4Motors motors;
Romi32U4Encoders encoders;

  struct countPair {
    int16_t right_count;
    int16_t left_count;
    int effort;
  };

  bool loopDone {false};
  countPair pairs[5] = {0};
  int effort_array[5] = {20, 40, 60, 80, 100};



void setup()
{

  Serial.begin(9600);

}



void loop()
{


  while(!loopDone) {

  for(int i {0}; i < (sizeof(pairs)/sizeof(pairs[0])); i++) {
    unsigned long current_time = millis();

    motors.setSpeeds(effort_array[i], effort_array[i]);

    while (((millis() - current_time)/1000) < 10) {}

    countPair current_pair = {encoders.getCountsRight(), encoders.getCountsLeft(), effort_array[i]}; 

    current_time = millis();
    motors.setSpeeds(0, 0);

    while (((millis() - current_time)/1000) < 5) {}
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();

    pairs[i] = current_pair;
  }

  loopDone = true;


  Serial.println("Left Count  || Right Count || Effort ");
  for(const auto &value: pairs) {

  Serial.print(value.left_count);
  Serial.print(" ");
  Serial.print(value.right_count);
  Serial.print(" ");
  Serial.print(value.effort);

}


}


}


