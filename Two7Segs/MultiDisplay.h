#include "Arduino.h"

#define NUM_SEG_PINS 7
#define CS_1 2
#define CS_2 3

class MultiDisplay{
  public:
  void displayNumber(int num);

  private:
  int SEG_PINS[NUM_SEG_PINS] = {12, 11, 10, 9, 8, 7, 6};
  void displayInt(int num);
  void writeToOnes(int num);
  void writeToTens(int num);
  void clearDisplay();
};