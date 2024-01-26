#ifndef HEXAPOD_H
#define HEXAPOD_H

class Hexapod {
public:
	Hexapod();

	void setupHexapod();
	void resetLegs();
	void walkForward();
	void moveLegBackward(int pos);
	void legsForward();
	void walkBackward();
	void turnRight();
	void turnLeft();
	void threaten();
};

#endif // !HEXAPOD_H
