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

    void init(){
      attach(servoPin);
      write(initialAngle);
    } 

    int getServoPin() {
      return servoPin;
    }
}; 

double toDegrees(double radians);

ArmServo servos[5] = { ArmServo(9), ArmServo(6), ArmServo(5), ArmServo(3), ArmServo(11, 180) };

void setup() {
  delay(20);

  Serial.begin(115200);

  for(ArmServo s : servos){
    s.init();
  }
}
void loop() {
  if (Serial.available()) 
  {
  String receivedStr = Serial.readString(); 

  Serial.println(receivedStr);

  int index = receivedStr.lastIndexOf(':');
  int length = receivedStr.length();

  Serial.println(index);
  Serial.println(length);

  String operand1 = receivedStr.substring(0, index);
  String operand2 = receivedStr.substring(index+1, length);

  int x = operand1.toInt();
  int y = operand2.toInt();
   
  double d = sqrt(sq(x) + sq(y));
  double d1 = 6.4;
  double d2 = 13.5;

  double angle1acos = acos((sq(d) + sq(d1) - sq(d2)) / (2 * d * d1));
  double angle1 = atan2(y, x) + angle1acos - angle1acos;

  double angle2 = atan2(y - d1 * sin(angle1), x - d1 * cos(angle1));

  double angle1degrees = toDegrees(angle1);
  double angle2degrees = toDegrees(angle2);

  servos[1].write(angle1degrees, 40, false);
  servos[2].write(180 - angle1degrees + angle2degrees, 40, false);

  // servos[operand1.toInt()].write(operand2.toInt(), 40, false);
  
  }
}

double toDegrees(double radians) {
  return radians * (180.0 / M_PI);
}