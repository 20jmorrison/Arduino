/**************************************
  File:     Obstacle.h
  Purpose:  Obstacle header
  Program:  Final project, Dino Game
  Author:   Jared Morrison
  Date:     12/13/2023
**************************************/


#include "LiquidCrystal_I2C.h"
#define MAX_OBSTACLES 4

class Obstacle {
  public:
    enum ObstacleType {CACTUS, DOUBLE_CACTUS, BIRD, ROCK, METEOR};  // Makes the program a bit more intuitive and easier to read
    Obstacle();
    void sendObstacle(ObstacleType OBSTACLE_TO_SEND, int OBSTACLE_SPEED);
    bool updateObstacles(LiquidCrystal_I2C &LCD, int dinoYPos);
    void resetObstacles();

  private:
    struct ObstacleStruct {
      ObstacleType type;
      int speed;
      int currentXPos;
      int currentYPos;
    };
    unsigned long counter;
    ObstacleStruct Obstacles[MAX_OBSTACLES];
    int obstacleIndex;
    void destroyObstacle(int indexToRemove);

};