#include "ArmServo.h"

class Grabber {
    public:
        ArmServo base = ArmServo(3);
        ArmServo pincers = ArmServo(11, 180);

        Grabber(){
        }

        void init(){
            base.init();
            pincers.init();
        }

        void close(){
            pincers.setAngle(0);
        }

        void open(){
            pincers.setAngle(180);
        }

};