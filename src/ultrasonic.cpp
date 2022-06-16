#include "ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo)
{
  this->trigPin = trig;
  this->echoPin = echo;
}

bool Ultrasonic::isNextBlockObstacle()
{
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, LOW);
  long duration = pulseIn(this->echoPin, HIGH);

  // Calculate the distance
  float distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  float distanceInch = distanceCm * CM_TO_INCH;

  if (distanceCm <= 19)
  {
    return true;
  }

  return false;
}