#include <Arduino.h>
#include <Romi32U4.h>


Romi32U4Motors motors;
Romi32U4Encoders encoders;

unsigned long time{0};

  struct countPair {
    int16_t right_count;
    int16_t left_count;
    int effort;
  };



void setup()
{

  Serial.begin(9600);




}



void loop()
{

  countPair pairs[5] = {0};
  
  countPair my_count = {0,0, 12};

  
  Serial.print("Time: ");
  time = millis();

  int16_t left_count = encoders.getCountsLeft();
  int16_t right_count = encoders.getCountsRight();

  delay(100);

  for(int i {0}; i < (sizeof(pairs)/sizeof(pairs[0]))+1; i++) {
    unsigned long current_time = millis();
  }


  

}


