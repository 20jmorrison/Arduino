/**************************************
  File:     Obstacle.cpp
  Purpose:  Obstacle implementation
  Program:  Final project, Dino Game
  Author:   Jared Morrison
  Date:     12/13/2023
**************************************/


#include "Obstacle.h"
#include "Arduino.h"


// Description: Obstacle constructor, inits everything to 0
// Param: None
// Return: None
Obstacle::Obstacle() {
  counter = 0;
  obstacleIndex = 0;
}


// Description: Sends an obstacle to the screen
// Param OBSTACLE_TO_SEND: Can be any obstacle from the ObstacleType enum define in Obstacle.h
// Param OBSTACLE_SPEED: Integer from 1-10, higher number is faster
// Return: None
void Obstacle::sendObstacle(ObstacleType OBSTACLE_TO_SEND, int OBSTACLE_SPEED) {
  if (obstacleIndex < MAX_OBSTACLES) {
    ObstacleStruct newObs;
    newObs.type = OBSTACLE_TO_SEND;
    newObs.speed = OBSTACLE_SPEED;
    newObs.currentXPos = 16;
    if (OBSTACLE_TO_SEND == BIRD || OBSTACLE_TO_SEND == METEOR) {
      newObs.currentYPos = 0;
    }
    else {
      newObs.currentYPos = 1;
    }

    Obstacles[obstacleIndex++] = newObs;
  }
}


// Description: Updates position of obstacles and checks for collisions
// Param LCD: Pointer to LCD display
// Param dinoYPos: Y-Position of dino
// Return: Returns true if there's been a collision, false if no collision
bool Obstacle::updateObstacles(LiquidCrystal_I2C &LCD, int dinoYPos) {
  bool collisionEncountered = false;
  counter++;
  for (int currObs = 0; currObs < obstacleIndex; currObs++) { // Looping through array of obstacles and updating each one's position
    if (Obstacles[currObs].currentXPos == 0) {
      destroyObstacle(currObs);
      LCD.setCursor(0,0);
      LCD.print(" ");
      LCD.setCursor(0,1);
      LCD.print(" ");
    }
    else {
      if (counter % (18 - Obstacles[currObs].speed) == 0) {
        LCD.setCursor(Obstacles[currObs].currentXPos, Obstacles[currObs].currentYPos);
        LCD.print(" ");
        Obstacles[currObs].currentXPos--;
        if (Obstacles[currObs].type == METEOR && Obstacles[currObs].currentXPos == 8) {
          Obstacles[currObs].currentYPos = 1;
          LCD.setCursor(Obstacles[currObs].currentXPos, Obstacles[currObs].currentYPos);

          LCD.write((uint8_t)5);
        }
        else {
          LCD.setCursor(Obstacles[currObs].currentXPos, Obstacles[currObs].currentYPos);
          switch (Obstacles[currObs].type) {
            case CACTUS:
              LCD.write((uint8_t)0);
              break;
            case DOUBLE_CACTUS:
              LCD.write((uint8_t)1);
              break;
            case BIRD:
              LCD.write((uint8_t)2);
              break;
            case ROCK:
              LCD.write((uint8_t)3);
              break;
            case METEOR:
              LCD.write((uint8_t)4);
              break;
            default:
              break;
          }
        }
        if ((Obstacles[currObs].currentYPos == dinoYPos) && (Obstacles[currObs].currentXPos == 2)){
          collisionEncountered = true;
        }
      }
    }
  }
  return collisionEncountered;
}


// Description: Removes an obstacle from the obstacle array to make room for a new one
// Param indexToRemove: Index of obstacle to remove
// Return: None
void Obstacle::destroyObstacle(int indexToRemove) {
  if (indexToRemove >= 0 && indexToRemove < obstacleIndex) {
    for (int i = indexToRemove; i < obstacleIndex - 1; ++i) {
      Obstacles[i] = Obstacles[i + 1];
    }
    obstacleIndex--;
  }
}


// Description: Resets obstacle array to null
// Param: None
// Return: None
void Obstacle::resetObstacles(){
  for (int i = 0; i < MAX_OBSTACLES; i++){
    ObstacleStruct placeholder;
    Obstacles[i] = placeholder;
  }
  obstacleIndex = 0;
}
