#include "MazeSolver.h"
#include "NewPing.h"


MazeSolver::MazeSolver(int l1, int l2, int r1, int r2, int t1, int e1, int t2, int e2, int t3, int e3)
{
	//Alloc memory for motors
	leftMotor = new int(2);
	rightMotor = new int(2);
	
	leftMotor[0] = l1;
	leftMotor[1] = l2;

	rightMotor[0] = r1;
	rightMotor[1] = r2;

	// Setting motors as output
	for (int i = 0; i < 2; i++){
		pinMode(leftMotor[i], OUTPUT);
		pinMode(rightMotor[i], OUTPUT);
	}

	// Creating sonar objects
	leftSonar = new NewPing(t1, e1, max_distance);
	frontSonar = new NewPing(t2, e2, max_distance);
	rightSonar = new NewPing(t3, e3, max_distance);


}



// Motor Driving Function
void MazeSolver::run(int l, int r)
{
	if (l >= 0 && r >= 0)
	{
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}

	else if (l < 0 && r < 0)
	{
		r = -r;
		l = -l;
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}

	else if (l > 0 && r < 0)
	{
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}

	else if (l < 0 && r > 0)
	{
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}

	else
	{
		digitalWrite(leftMotor[0], LOW);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		digitalWrite(rightMotor[1], LOW);
	}
}


int MazeSolver::leftDistance()
{
	return leftSonar->ping() / US_ROUNDTRIP_CM;
}

int MazeSolver::rightDistance()
{
	return rightSonar->ping() / US_ROUNDTRIP_CM;
}

int MazeSolver::frontDistance()
{
	return frontSonar->ping() / US_ROUNDTRIP_CM;
}



void MazeSolver::leftTurn()
{
	run(0, 0);
	delay(400);
	run(0, speed);
	delay(leftTurnDelay);
}

void MazeSolver::rightTurn()
{
	run(0, 0);
	delay(400);
	run(speed, 0);
	delay(rightTurnDelay);
}


void MazeSolver::uTurn()
{
	run(0, 0);
	delay(400);
	run(speed, -speed);
	delay(uTurnDelay);
}