#include "MazeSolver.h"

MazeSolver robot(5, 6, 3, 4, 9, 8, 11, 10, 13, 12);
// l1, l2, r1, r2, t1, e1, t2, e2, t3, e3

const int distance = 20;
const int minimum = 6;

int leftBoundMax = 12;
int leftBoundMin = 6;

void setup()
{
	Serial.begin(9600);
	Serial.println("Ready for Solving the maze");
	robot.speed = 120;
	robot.max_distance = 100;
	robot.leftTurnDelay = 750;
	robot.rightTurnDelay = 825;
	robot.uTurnDelay = 750;
	
	delay(3000);
}

void loop()
{
	robot.front = robot.frontDistance();
	robot.left = robot.leftDistance();
	robot.right = robot.rightDistance();

	if (robot.front > minimum){
		if (robot.left > leftBoundMin && robot.left < leftBoundMax){
			robot.run(robot.speed, robot.speed);
		}

		if (robot.left >= leftBoundMax){
			robot.run(robot.speed - 30, robot.speed);
		}

		if (robot.left < leftBoundMin){
			robot.run(robot.speed, robot.speed - 30);
		}
	}
   

	if (robot.left <= distance && robot.right > distance && robot.front < minimum) robot.rightTurn();

	if (robot.left > distance && robot.right > distance && robot.front < minimum) robot.leftTurn();

	if (robot.left <= distance && robot.front <= minimum && robot.right <= distance) robot.uTurn();

}
