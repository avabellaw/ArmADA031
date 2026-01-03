#ifndef ARMSERVO_H
#define ARMSERVO_H 

#include <VarSpeedServo.h>

class ArmServo : public VarSpeedServo {
private:
  int servoPin;
  int initialAngle;
  int speed;

public:
  ArmServo(int servoPin, int initialAngle = 90, int speed = 20) {
    this->servoPin = servoPin;
    this->initialAngle = initialAngle;
    this->speed = speed;

    pinMode(servoPin, OUTPUT);
  }

  void init() {
    attach(servoPin);
    write(initialAngle);
  }

  int getServoPin() {
    return servoPin;
  }

  void setSpeed(int speed) {
    this->speed = speed;
  }

  void setAngle(int angle, bool isBlocking = false) {
    if (angle > 180 || angle < 0) {
        Serial.println("Angle is " + String(angle % 180) + " out of bounds.");
    } else {
        Serial.println("Angle set to: " + String(angle) + " degrees");
        write(angle, speed, isBlocking);
    }
  }
};

#endif