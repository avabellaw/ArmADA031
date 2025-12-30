#include <Servo.h>

int angle = 90;        //Angle of rotation of the servo

class ArmServo : public Servo {
  private:
    int servoPin;

  public:
    ArmServo(int servoPin) {
      this->servoPin = servoPin; 

      pinMode(servoPin, OUTPUT);
    }

    void init(){
      attach(servoPin);
      write(angle);
    } 

    int getServoPin() {
      return servoPin;
    }
}; 

ArmServo servos[5] = { ArmServo(9), ArmServo(6), ArmServo(5), ArmServo(3), ArmServo(11) };

void setup() {
  delay(20);

  Serial.begin(115200);

  for(ArmServo s : servos){
    s.init();
    Serial.println(s.getServoPin());
  }
}
void loop() {
  // if (Serial.available()) 
  // {
  // String receivedStr = Serial.readString(); 

  // Serial.println(receivedStr);

  // int index = receivedStr.lastIndexOf(':');
  // int length = receivedStr.length();

  // Serial.println(index);
  // Serial.println(length);

  // String operand1 = receivedStr.substring(0, index);
  // String operand2 = receivedStr.substring(index+1, length);
  // Serial.println(operand1);  
  // Serial.println(operand2);  

  // servos[operand1.toInt()].write(operand2.toInt());
  
  // }//endof if 
}