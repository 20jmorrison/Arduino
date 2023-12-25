#include "MultiDisplay.h"

void MultiDisplay::displayNumber(int num){
  int ones = num % 10;
  int tens = (num / 10) % 10;
  clearDisplay();
  writeToTens(tens);
  writeToOnes(ones);
}

void MultiDisplay::writeToTens(int num){
  digitalWrite(CS_1, HIGH);
  displayInt(num);
  delay(10);
  digitalWrite(CS_1, LOW);
}

void MultiDisplay::writeToOnes(int num){
  digitalWrite(CS_2, HIGH);
  displayInt(num);
  delay(10);
  digitalWrite(CS_2, LOW);
}

void MultiDisplay::clearDisplay() {
  for (int i = 0; i < NUM_SEG_PINS; i++) {
    digitalWrite(SEG_PINS[i], HIGH);
  }
  delay(1);
}

void MultiDisplay::displayInt(int value) {
  const byte digitCodes[10] = {
  // PCBADEGF
    B01111101, // 0
    B01100000, // 1
    B00111110, // 2
    B01111010, // 3
    B01100011, // 4
    B01011011, // 5
    B01011111, // 6
    B01110000, // 7
    B01111111, // 8
    B01110011  // 9
  };

  if (value >= 0 && value <= 9) {
    for (int i = 0; i < NUM_SEG_PINS; i++) {
      digitalWrite(SEG_PINS[i], !bitRead(digitCodes[value], i));
    }
  }
}