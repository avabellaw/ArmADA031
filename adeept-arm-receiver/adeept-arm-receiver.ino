#include "Arm.h"

Arm arm = Arm();

void checkForSerialMessages();

void setup() {
  delay(20);

  Serial.begin(115200);
}
void loop() {
    checkForSerialMessages();

    arm.update();
}

void checkForSerialMessages(){
    if (Serial.available()) {
        String receivedStr = Serial.readString();

        // Format serial message as "x:y:z"
        int lastColonIndex = receivedStr.lastIndexOf(':');
        int firstColonIndex = receivedStr.indexOf(':');
        int length = receivedStr.length();

        String xStr = receivedStr.substring(0, firstColonIndex);
        String yStr = receivedStr.substring(firstColonIndex + 1, lastColonIndex);
        String zStr = receivedStr.substring(lastColonIndex + 1, length);

        // Extract coords from serial message string "x:y:z"
        double x = xStr.toDouble();
        double y = yStr.toDouble();
        double z = zStr.toDouble();

        Serial.println("Inputted values: x=" + xStr + ", y=" + yStr + ", z=" + zStr);

        arm.moveTo(x, y, z);
    }
}