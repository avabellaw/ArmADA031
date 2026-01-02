#include "Arm.h"

double toDegrees(double radians);
double getBaseAngle(int x, int y);

Arm arm = Arm();

void setup() {
  delay(20);

  Serial.begin(115200);
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

    arm.moveTo(x, y, z);
  }
}