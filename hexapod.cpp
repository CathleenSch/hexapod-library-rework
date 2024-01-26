#include "hexapod.h"
#include "Arduino.h"

#include <Servo.h>
#include "servo_angles.h"

// {{front_left_bot, front_left_top}, {mid_left_bot, mid_left_top}, {back_left_bot, back_left_top}, {front_right_bot, front_right_top}, {mid_right_bot, mid_right_top}, {back_right_bot, back_right_top}}
// FL, ML, BL, FR, MR, BR
Servo legs[6][2];
Servo head;

Hexapod::Hexapod() {}

void Hexapod::setupServos() {
    legs[0][0].attach(2);
    legs[0][1].attach(3);
    legs[1][0].attach(4);
    legs[1][1].attach(5);
    legs[2][0].attach(6);
    legs[2][1].attach(7);
    legs[3][0].attach(8);
    legs[3][1].attach(9);
    legs[4][0].attach(10);
    legs[4][1].attach(11);
    legs[5][0].attach(12);
    legs[5][1].attach(13);
    head.attach(14);

    resetLegs();
}

void Hexapod::resetLegs() {
    for (int i = 0; i < 6; i++) {
        legs[i][0].write(angles[i][0]);
        legs[i][1].write(angles[i][1]);
    }

    head.write(head_angle);
}

void Hexapod::walkForward() {
    // Raise mid left, front right and back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + i);
    }

    delay(50);

    // Move mid left, front right and back right legs forward
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1]);
        legs[1][1].write(angles[1][1] + i);
        legs[2][1].write(angles[2][1]);
        legs[3][1].write(angles[3][1] - i);
        legs[4][1].write(angles[4][1]);
        legs[5][1].write(angles[5][1] - i);
    }

    delay(50);

    // Lower mid left, front right and back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - 45 + i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + 45 - i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + 45 - i);
    }

    delay(50);

    // Raise front left, back left and mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + i);
        legs[5][0].write(angles[5][0]);
    }

    delay(50);

    // Move front left, back left and mid right legs forward
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1] + i);
        legs[1][1].write(angles[1][1]);
        legs[2][1].write(angles[2][1] + i);
        legs[3][1].write(angles[3][1]);
        legs[4][1].write(angles[4][1] - i);
        legs[5][1].write(angles[5][1]);
    }

    delay(50);

    // Lower front left, back left and mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - 45 + i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - 45 + i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + 45 - i);
        legs[5][0].write(angles[5][0]);
    }
}

void Hexapod::moveLegBackward(int pos) {
    for (int i = 0; i <= 60; i++) {
        if (pos >= 3) {
            legs[pos][0].write(angles[pos][0] + i); // raise right leg
        }
        else {
            legs[pos][0].write(angles[pos][0] - i); // raise left leg
        }
    }

    delay(50);

    for (int i = 0; i <= 45; i++) {
        if (pos >= 3) {
            legs[pos][1].write(angles[pos][1] + i); // move right leg backward
        }
        else {
            legs[pos][1].write(angles[pos][1] - i); // move left leg backward
        }
    }

    delay(50);

    for (int i = 0; i <= 45; i++) {
        if (pos >= 3) {
            legs[pos][0].write(angles[pos][0] + 45 - i); // lower right leg
        }
        else {
            legs[pos][0].write(angles[pos][0] - 45 + i); // lower left leg
        }
    }
}

void Hexapod::legsForward() {
    for (int pos = 0; pos < 6; pos++) {
        if (pos == 0 || pos == 3) {
            for (int i = 0; i < 25; i++) {
                if (pos == 0) {
                    legs[pos][1].write(angles[pos][1] - 25 + i);
                }
                else {
                    legs[pos][1].write(angles[pos][1] + 25 - i);
                }
            }
        }

        for (int i = 0; i <= 45; i++) {
            if (pos > 3) {
                legs[pos][1].write(angles[pos][1] - i); // move right leg far forward
            }
            else if (pos > 0 && pos < 3) {
                legs[pos][1].write(angles[pos][1] + i); // move left leg far forward
            }
        }
    }
}

void Hexapod::walkBackward() { 
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            delay(200);
        }
        moveLegBackward(i);
        delay(25);

        if (i == 5) {
            delay(200);
        }
    }

    legsForward();
    delay(50);
}

void Hexapod::turnRight() {
    // Raise front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + i);
        legs[5][0].write(angles[5][0]);
    }

    delay(50);

    // Move front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1] + i);
        legs[1][1].write(angles[1][1]);
        legs[2][1].write(angles[2][1] + i);
        legs[3][1].write(angles[3][1]);
        legs[4][1].write(angles[4][1] + i);
        legs[5][1].write(angles[5][1]);
    }

    delay(50);

    // Lower front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - 45 + i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - 45 + i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + 45 - i);
        legs[5][0].write(angles[5][0]);
    }

    delay(50);

    // Raise mid left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + i);
    }

    delay(50);

    // Move ,id left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1]);
        legs[1][1].write(angles[1][1] + i);
        legs[2][1].write(angles[2][1]);
        legs[3][1].write(angles[3][1] + i);
        legs[4][1].write(angles[4][1]);
        legs[5][1].write(angles[5][1] + i);
    }

    delay(50);

    // Lower mid left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - 45 + i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + 45 - i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + 45 - i);
    }
}

void Hexapod::turnLeft() { 
    // Raise front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + i);
        legs[5][0].write(angles[5][0]);
    }

    delay(50);

    // Move front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1] - i);
        legs[1][1].write(angles[1][1]);
        legs[2][1].write(angles[2][1] - i);
        legs[3][1].write(angles[3][1]);
        legs[4][1].write(angles[4][1] - i);
        legs[5][1].write(angles[5][1]);
    }

    delay(50);

    // Lower front left, back left, mid right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0] - 45 + i);
        legs[1][0].write(angles[1][0]);
        legs[2][0].write(angles[2][0] - 45 + i);
        legs[3][0].write(angles[3][0]);
        legs[4][0].write(angles[4][0] + 45 - i);
        legs[5][0].write(angles[5][0]);
    }

    delay(50);

    // Raise mid left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + i);
    }

    delay(50);

    // Move ,id left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][1].write(angles[0][1]);
        legs[1][1].write(angles[1][1] - i);
        legs[2][1].write(angles[2][1]);
        legs[3][1].write(angles[3][1] - i);
        legs[4][1].write(angles[4][1]);
        legs[5][1].write(angles[5][1] - i);
    }

    delay(50);

    // Lower mid left, front right, back right legs
    for (int i = 0; i <= 45; i++) {
        legs[0][0].write(angles[0][0]);
        legs[1][0].write(angles[1][0] - 45 + i);
        legs[2][0].write(angles[2][0]);
        legs[3][0].write(angles[3][0] + 45 - i);
        legs[4][0].write(angles[4][0]);
        legs[5][0].write(angles[5][0] + 45 - i);
    }
}

void Hexapod::threaten() {


}