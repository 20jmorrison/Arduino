/******************
Program: Arduino Hello World
Purpose: Print "Hello World" to console over serial
Author: Jared Morrison
Date: 12/24/2023
******************/


#define BAUD 9600

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  Serial.println("Hello World");
  delay(500);
}
