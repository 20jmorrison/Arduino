/**********************************************************
Program: Two 7 Segment Display
Purpose: Count up to 99 on two seperate 7 segment displays
Author: Jared Morrison
Date: 12/24/2023
**********************************************************/


#define INTERVAL 500
#define NUM_SEG_PINS 7

#include "MultiDisplay.h"

unsigned long PREV_TIME = 0;
int count = 0;
MultiDisplay DisplayDriver;

void setup() {
  pinMode(CS_1, OUTPUT);
  pinMode(CS_2, OUTPUT);
  digitalWrite(CS_1, HIGH);
  digitalWrite(CS_2, HIGH);
  int SEG_PINS[NUM_SEG_PINS] = {12, 11, 10, 9, 8, 7, 6};
  for (int i : SEG_PINS){
    pinMode(i, OUTPUT);
  }

}

void loop() {

  if (millis() % PREV_TIME >= INTERVAL){
    PREV_TIME = millis();
    count = (count > 99) ? 0 : count + 1;
  }
  
  DisplayDriver.displayNumber(count);
}
