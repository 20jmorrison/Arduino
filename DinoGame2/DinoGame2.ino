/***********************************************************
Program: Dino Game 2
Purpose: Recreation of dino game I made for Final Project
Author: Jared Morrison
Date: 12/24/2023
***********************************************************/

#define BUTTON 4
#define BAUD 9600
#define NUM_SEG_PINS 7

#include <LiquidCrystal.h>
#include "MultiDisplay.h"
#include "Sprites.h"

const int rs = 21, en = 20, d4 = 19, d5 = 18, d6 = 17, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MultiDisplay DisplayDriver;

bool gameStarted = false;
int score = 0;

void setup() {
  Serial.begin(BAUD);
  
  int SEG_PINS[NUM_SEG_PINS] = {12, 11, 10, 9, 8, 7, 6};
  for (int i : SEG_PINS){
    pinMode(i, OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(CS_1, OUTPUT);
  pinMode(CS_2, OUTPUT);

  digitalWrite(CS_1, HIGH);
  digitalWrite(CS_2, HIGH);
  
  lcd.begin(16, 2);
  lcd.createChar(7, dino);
  lcd.createChar(6, dinob);
  lcd.createChar(0, cactus);
  lcd.createChar(1, double_cactus);
  lcd.createChar(2, bird);
  lcd.createChar(3, rock);
  lcd.createChar(4, meteor);
  lcd.createChar(5, crashed_meteor);
  lcd.setCursor(0, 0);
  lcd.print("PRESS BUTTON");
  lcd.setCursor(0, 1);
  lcd.print("TO START...");
  
  attachInterrupt(BUTTON, buttonPress, FALLING);
}


void loop() {
  DisplayDriver.displayNumber(score);
}


void buttonPress(){
  if(!gameStarted){
    gameStarted = true;
  }
  score++;
  Serial.println("Button Has Been Pressed");
}