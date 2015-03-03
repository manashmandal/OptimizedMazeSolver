#include "NewPing.h"


class MazeSolver
{
public:
	 //Change this things
	 int speed = 120;
	 int max_distance = 100;
	 int leftTurnDelay = 750;
	 int rightTurnDelay = 825;
	 int uTurnDelay = 750;

	 


	 //Sonars
	 NewPing* frontSonar;
	 NewPing* leftSonar;
	 NewPing* rightSonar;


	 //Distance variables
	 int front, left, right;

	 //Motor pins
	 int* leftMotor;
	 int* rightMotor;

	 //Constructor for setting motor pins output and setting the sonars
	MazeSolver(int l1, int l2, int r1, int r2, int t1, int e1, int t2, int e2, int t3, int e3);

	void run(int l, int r);
	

	int leftDistance();
	int rightDistance();
	int frontDistance();


	void rightTurn();
	void leftTurn();
	void uTurn();

};

