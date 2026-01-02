#include "ArmServo.h"

class Grabber {
    private:
        ArmServo base = ArmServo(3);
        ArmServo pincers = ArmServo(11, 180);

    public:
        Grabber(){
            base.init();
            pincers.init();
        }

        void close(){
            pincers.setAngle(0);
        }

        void open(){
            pincers.setAngle(180);
        }

        void setPincersAngle(int angle) {
            pincers.setAngle(angle);
        }

        void setBaseAngle(int angle) {
            base.setAngle(angle);
        }

};