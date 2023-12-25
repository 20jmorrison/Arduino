/***********************************************************
Program: Dino Game 2
Purpose: Recreation of dino game I made for Final Project
Author: Jared Morrison
Date: 12/24/2023
***********************************************************/

#define BUTTON 4
#define BAUD 9600
#define NUM_SEG_PINS 7
#define SPAWN_INTERVAL 1000

#include <LiquidCrystal.h>
#include "MultiDisplay.h"
#include "Sprites.h"
#include "Obstacle.h"

const int rs = 21, en = 20, d4 = 19, d5 = 18, d6 = 17, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MultiDisplay ScoreDriver;
Obstacle ObstacleDriver;

bool gameStarted = false;
bool lcdNeedsClearing = false;
unsigned long prevMillis = 0;
int score = 0;
int speed = 4;


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
  if (lcdNeedsClearing) {     // Used because lcd can't be cleared from an interrupt function, and I need some way to clear the display on button press
    lcd.clear();              // Solution was to use a flag
    lcdNeedsClearing = false;
  }

  if (gameStarted) {
    if (millis() - prevMillis >= SPAWN_INTERVAL) {
      prevMillis = millis();
      Obstacle::ObstacleType newObstacleType;
      newObstacleType = selectRandomObstacleType();
      ObstacleDriver.sendObstacle(newObstacleType, speed);  // Generating a new obstacle and sending it to the screen
      if ((score % 3 == 0) && speed < 12) {
        speed++;
      }

      score++;
    }

    ScoreDriver.displayNumber(score);
    int dinoYPos = digitalRead(BUTTON);
    displayDino(dinoYPos);

    if (ObstacleDriver.updateObstacles(lcd, dinoYPos)) { // updateObstacles will return true if there's a collision
      gameOver();
    }
  }
}

void displayDino(int yPos){
  int posToErase = (yPos == 1) ? 0 : 1;
  lcd.setCursor(2, posToErase);
  lcd.write(" ");
  lcd.setCursor(2, yPos);
  lcd.write((uint8_t)7);
}

void gameOver(){
  gameStarted = false;
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("GAME LOST");
  lcd.setCursor(0, 1);
  lcd.print("SCORE: ");
  lcd.print(score);
}


void buttonPress(){
  if(!gameStarted){
    score = 0;
    speed = 4;
    ObstacleDriver.resetObstacles();
    gameStarted = true;
    lcdNeedsClearing = true;
  }
}


Obstacle::ObstacleType selectRandomObstacleType() {
  int typeNum = rand() % 5;
  return static_cast<Obstacle::ObstacleType>(typeNum);
}