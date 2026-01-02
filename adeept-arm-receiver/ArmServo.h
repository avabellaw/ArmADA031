#include <VarSpeedServo.h>

class ArmServo : public VarSpeedServo {
private:
  int servoPin;
  int initialAngle;

public:
  ArmServo(int servoPin, int initialAngle = 90) {
    this->servoPin = servoPin;
    this->initialAngle = initialAngle;

    pinMode(servoPin, OUTPUT);
  }

  void init() {
    attach(servoPin);
    write(initialAngle);
  }

  int getServoPin() {
    return servoPin;
  }
};