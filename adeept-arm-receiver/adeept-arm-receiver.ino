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

double toDegrees(double radians);
double getBaseAngle(int x, int y);

// base, angle1, angle2, grabberBase, grabberOpenClose (inital=closed)
ArmServo servos[5] = { ArmServo(9), ArmServo(6), ArmServo(5), ArmServo(3), ArmServo(11, 180) };

void setup() {
  delay(20);

  Serial.begin(115200);

  for (ArmServo s : servos) {
    s.init();
  }
}
void loop() {
  if (Serial.available()) {
    String receivedStr = Serial.readString();

    Serial.println(receivedStr);

    int index = receivedStr.lastIndexOf(':');
    int middle = receivedStr.indexOf(':');
    int length = receivedStr.length();

    // Extract coords from serial message string "x:y:z"
    String operand1 = receivedStr.substring(0, middle);
    String operand2 = receivedStr.substring(middle + 1, index);
    String operand3 = receivedStr.substring(index + 1, length);

    Serial.println("" + operand1 + ", " + operand2 + ", " + operand3);

    double x = operand1.toDouble();
    double y = operand2.toDouble();
    double z = operand3.toDouble();

    double d1 = 6.5;
    double d2 = 13.5;

    double baseAngle = getBaseAngle(x, y);

    double baseHyp = sqrt(sq(x) + sq(y));
    double l = sqrt(sq(baseHyp) + sq(z));

    // cos(A) = b^2 + c^2 - a^2 / 2bc
    double angle2theta1 = acos((sq(d1) + sq(l) - sq(d2)) / (2 * d1 * l));

    // sin(theta2) = opposite / hyp
    double angle2theta2 = asin(z / l);

    double angle1 = 180 - toDegrees(angle2theta1 + angle2theta2);

    // The law of cosines
    double angle2 = 360 - 90 - toDegrees(acos((sq(d2) + sq(d1) - sq(l)) / (2 * d2 * d1)));

    Serial.print("angle1: ");
    Serial.println(angle1);

    Serial.print("angle2");
    Serial.println(angle2);

    Serial.print("baseAngle");
    Serial.println(baseAngle);

    servos[0].write(baseAngle, 40, false);
    servos[1].write(angle1, 40, false);
    servos[2].write(angle2, 40, false);
  }
}

double toDegrees(double radians) {
  return radians * (180.0 / M_PI);
}

double getBaseAngle(int x, int y) {
    // theta = atan(opposite / adj)
    return toDegrees(atan2(y, x));
}