#pragma once
#include <Arduino.h>
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

class Ultrasonic
{
private:
  int trigPin;
  int echoPin;

public:
  /**
   * @brief Construct a new Ultrasonic object
   *
   * @param trig Pass the trig pin as given in int notation in Arduino platform
   * @param echo Pass the trig pin as given in int notation in Arduino platform
   */
  Ultrasonic(int trig, int echo);
  /**
   * @brief check if the block in the facing direction of the ultrasonic sensor is an obstacle
   *
   * @return true - Is an obstacle
   * @return false - Obstacle not detected
   */
  bool isNextBlockObstacle();
};