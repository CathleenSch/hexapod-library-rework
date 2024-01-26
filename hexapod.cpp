#include "hexapod.h"
#include "Arduino.h"
#include "servo_angles.h"
#include "hexapod_config.h"
#include <Servo.h>

// {{front_left_bot, front_left_top}, {mid_left_bot, mid_left_top}, {back_left_bot, back_left_top}, {front_right_bot, front_right_top}, {mid_right_bot, mid_right_top}, {back_right_bot, back_right_top}}
// FL, ML, BL, FR, MR, BR
Servo head;
Servo legs[6][2];
Adafruit_NeoPixel lights = Adafruit_NeoPixel(6, A1, NEO_GRB + NEO_KHZ800);


Hexapod::Hexapod() {}

void Hexapod::setupHexapod() {
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

	pinMode(pingPin, INPUT);
	pinMode(trigPin, OUTPUT);
	Serial.begin(9600);

	lights.begin();
	lights.setBrightness(50);
	delay(2000);
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

	delay(walkingSpeed);

	// Move mid left, front right and back right legs forward
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1]);
		legs[1][1].write(angles[1][1] + i);
		legs[2][1].write(angles[2][1]);
		legs[3][1].write(angles[3][1] - i);
		legs[4][1].write(angles[4][1]);
		legs[5][1].write(angles[5][1] - i);
	}

	delay(walkingSpeed;

	// Lower mid left, front right and back right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0]);
		legs[1][0].write(angles[1][0] - 45 + i);
		legs[2][0].write(angles[2][0]);
		legs[3][0].write(angles[3][0] + 45 - i);
		legs[4][0].write(angles[4][0]);
		legs[5][0].write(angles[5][0] + 45 - i);
	}

	delay(walkingSpeed);

	// Raise front left, back left and mid right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0] - i);
		legs[1][0].write(angles[1][0]);
		legs[2][0].write(angles[2][0] - i);
		legs[3][0].write(angles[3][0]);
		legs[4][0].write(angles[4][0] + i);
		legs[5][0].write(angles[5][0]);
	}

	delay(walkingSpeed);

	// Move front left, back left and mid right legs forward
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1] + i);
		legs[1][1].write(angles[1][1]);
		legs[2][1].write(angles[2][1] + i);
		legs[3][1].write(angles[3][1]);
		legs[4][1].write(angles[4][1] - i);
		legs[5][1].write(angles[5][1]);
	}

	delay(walkingSpeed);

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

	delay(walkingSpeed);

	for (int i = 0; i <= 45; i++) {
		if (pos >= 3) {
			legs[pos][1].write(angles[pos][1] + i); // move right leg backward
		}
		else {
			legs[pos][1].write(angles[pos][1] - i); // move left leg backward
		}
	}

	delay(walkingSpeed);

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
	delay(walkingSpeed);
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

	delay(walkingSpeed);

	// Move front left, back left, mid right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1] + i);
		legs[1][1].write(angles[1][1]);
		legs[2][1].write(angles[2][1] + i);
		legs[3][1].write(angles[3][1]);
		legs[4][1].write(angles[4][1] + i);
		legs[5][1].write(angles[5][1]);
	}

	delay(walkingSpeed);

	// Lower front left, back left, mid right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0] - 45 + i);
		legs[1][0].write(angles[1][0]);
		legs[2][0].write(angles[2][0] - 45 + i);
		legs[3][0].write(angles[3][0]);
		legs[4][0].write(angles[4][0] + 45 - i);
		legs[5][0].write(angles[5][0]);
	}

	delay(walkingSpeed);

	// Raise mid left, front right, back right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0]);
		legs[1][0].write(angles[1][0] - i);
		legs[2][0].write(angles[2][0]);
		legs[3][0].write(angles[3][0] + i);
		legs[4][0].write(angles[4][0]);
		legs[5][0].write(angles[5][0] + i);
	}

	delay(walkingSpeed);

	// Move ,id left, front right, back right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1]);
		legs[1][1].write(angles[1][1] + i);
		legs[2][1].write(angles[2][1]);
		legs[3][1].write(angles[3][1] + i);
		legs[4][1].write(angles[4][1]);
		legs[5][1].write(angles[5][1] + i);
	}

	delay(walkingSpeed);

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

	delay(walkingSpeed);

	// Move front left, back left, mid right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1] - i);
		legs[1][1].write(angles[1][1]);
		legs[2][1].write(angles[2][1] - i);
		legs[3][1].write(angles[3][1]);
		legs[4][1].write(angles[4][1] - i);
		legs[5][1].write(angles[5][1]);
	}

	delay(walkingSpeed);

	// Lower front left, back left, mid right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0] - 45 + i);
		legs[1][0].write(angles[1][0]);
		legs[2][0].write(angles[2][0] - 45 + i);
		legs[3][0].write(angles[3][0]);
		legs[4][0].write(angles[4][0] + 45 - i);
		legs[5][0].write(angles[5][0]);
	}

	delay(walkingSpeed);

	// Raise mid left, front right, back right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][0].write(angles[0][0]);
		legs[1][0].write(angles[1][0] - i);
		legs[2][0].write(angles[2][0]);
		legs[3][0].write(angles[3][0] + i);
		legs[4][0].write(angles[4][0]);
		legs[5][0].write(angles[5][0] + i);
	}

	delay(walkingSpeed);

	// Move ,id left, front right, back right legs
	for (int i = 0; i <= 45; i++) {
		legs[0][1].write(angles[0][1]);
		legs[1][1].write(angles[1][1] - i);
		legs[2][1].write(angles[2][1]);
		legs[3][1].write(angles[3][1] - i);
		legs[4][1].write(angles[4][1]);
		legs[5][1].write(angles[5][1] - i);
	}

	delay(walkingSpeed);

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

int getDistance() {
	int cm = sr04.Distance();
	if (cm > 100) {
		return 0;
	}
	else {
		return cm;
	}
}

void Hexapod::threaten() {
	int cm = getDistance();
	delay(100);
	if (cm < 20 && !(cm == 0)) {
		Serial.println(cm);
		for (int i = 0; i <= 60; i++) {
			legs[2][1].write(angles[2][1] - 60);
			legs[5][1].write(angles[5][1] + 60);
		}

		for (int i = 0; i <= 80; i++) {
			legs[2][0].write(angles[2][0] - 80);
			legs[5][0].write(angles[5][0] + 80);
		}

		for (int i = 0; i <= 45; i++) {
			legs[1][1].write(angles[1][1] + 45);
			legs[4][1].write(angles[4][1] - 45);
			legs[0][1].write(angles[0][1] + 45);
			legs[0][0].write(angles[0][0] - 45);
			legs[3][1].write(angles[3][1] - 45);
			legs[3][0].write(angles[3][0] + 45);
		}

		for (int i = 0; i < 6; i++) {
			lights.setPixelColor(i, lights.Color(255, 0, 0));
			lights.show();
		}
		delay(100);
	}
	else {
		resetLegs();
		delay(100);
		while (cm >= 20 || cm == 0) {
			cm = getDistance();
			delay(100);
			Serial.println(cm);
			for (int i = 0; i < 6; i++) {
				lights.setPixelColor(i, lights.Color(0, 255, 0));
				lights.show();
			}
		}
	}
}