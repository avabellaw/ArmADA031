#include "ArmServo.h"
#include "Grabber.h"

class Arm {
    private:
        // base, angle1, angle2, grabberBase, grabberOpenClose (inital=closed)
        ArmServo base = ArmServo(9);
        ArmServo shoulder = ArmServo(6);
        ArmServo elbow = ArmServo(5);

        Grabber grabber = Grabber();
        
        static const double d1 = 6.5; // cm - Upperarm length
        static const double d2 = 13.5; // cm - Forearm length (including grabber)

        double toDegrees(double radians) {
            return radians * (180.0 / M_PI);
        }

        double getBaseAngle(int x, int y) {
            // theta = atan(opposite / adj)
            return toDegrees(atan2(abs(y), x));
        }

        /**
         * @brief Set the angles of the positional servos
         * @param baseAngle Angle of the horizontal base servo
         * @param shoulderAngle Servo 2
         * @param elbowAngle Servo 3
         */
        void setAngles(double baseAngle, double shoulderAngle, double elbowAngle) {
            Serial.print("baseAngle: ");
            Serial.println(baseAngle);

            Serial.print("shoulderAngle");
            Serial.println(shoulderAngle);

            Serial.print("elbowAngle");
            Serial.println(elbowAngle);

            base.setAngle(baseAngle);
            shoulder.setAngle(shoulderAngle);
            elbow.setAngle(elbowAngle);
        }

    public:
        Arm(){
            base.init();
            shoulder.init();
            elbow.init();
        }

        /**
         * @brief Moves the arm to specific coordinates
         * @param x, y, z The coordinates
         */
        void moveTo(double x, double y, double z) {
            double baseAngle = getBaseAngle(x, y);

            double baseHyp = sqrt(sq(x) + sq(y));
            double l = sqrt(sq(baseHyp) + sq(z));

            // cos(A) = b^2 + c^2 - a^2 / 2bc
            double angle2theta1 = acos((sq(d1) + sq(l) - sq(d2)) / (2 * d1 * l));

            // sin(theta2) = opposite / hyp
            double angle2theta2 = asin(z / l);

            double angle1 = toDegrees(angle2theta1 + angle2theta2);

            // The law of cosines
            double angle2 = 360 - 90 - toDegrees(acos((sq(d2) + sq(d1) - sq(l)) / (2 * d2 * d1)));

            Serial.print("angle2theta1: ");
            Serial.println(angle2theta1);

            Serial.print("angle2theta2: ");
            Serial.println(angle2theta2);

            setAngles(baseAngle, angle1, angle2);
        }
};