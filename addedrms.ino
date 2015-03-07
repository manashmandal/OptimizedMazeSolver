#include <NewPing/Newping.h>
#include <math.h>

float correction = 5.00; //Change it 

#define MAX_DISTANCE 400
#define min 10

int leftBoundMax = 14;
int leftBoundMin = 8;
int speedReducer = 30;

NewPing leftSonar(9, 8, MAX_DISTANCE);
NewPing frontSonar(11, 10, MAX_DISTANCE);
NewPing rightSonar(13, 12, MAX_DISTANCE);

int leftMotor[] = { 5, 6 };
int rightMotor[] = { 3, 4 };

int speed = 120; // Change it at your will
int left, front, right;

void setMotors(int l, int r)
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
		r = -r;
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}
	else if (l < 0 && r > 0)
	{
		l = -l;
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

int leftDistance()
{
	return leftSonar.ping() / US_ROUNDTRIP_CM;
}

int rightDistance()
{
	return rightSonar.ping() / US_ROUNDTRIP_CM;
}


int frontDistance()
{
	return frontSonar.ping() / US_ROUNDTRIP_CM;
}

void setup()
{
	Serial2.begin(9600);
	for (int i = 0; i < 2; i++){
		pinMode(leftMotor[i], OUTPUT);
		pinMode(rightMotor[i], OUTPUT);
	}
	Serial2.println("Serial initialized");
	delay(3000);
	/* add setup code here */
}


void updateDistance()
{
	front = frontDistance();
	left = leftDistance();
	right = rightDistance();
	Serial2.println("Front: " + String(front));
	Serial2.println("Left: " + String(left));
	Serial2.println("Right: " + String(right));

}



char decision()
{
	float leftRight_RMS, leftFront_RMS, rightFront_RMS;

	if (front > left && front > right)
	{
		leftRight_RMS = sqrt((pow(left, 2) + pow(right, 2)) / 2);
		if (front > leftRight_RMS + correction) return 'f';
		else return 'u';
	}

	else if (left > right && left > front)
	{
		rightFront_RMS = sqrt((pow(right, 2) + pow(front, 2)) / 2);
		if (left > rightFront_RMS + correction) return 'l';
		else return 'u';
	}

	else if (right > left && right > front)
	{
		leftFront_RMS = sqrt((pow(left, 2) + pow(front, 2)) / 2);
		if (right > leftFront_RMS + correction) return 'r';
		else return 'u';
	}


	/* 

	// Uncomment for debugging purpose
	Serial2.println("Left-Right RMS: " + String(leftRight_RMS));
	Serial2.println("Front-Right RMS: " + String(rightFront_RMS));
	Serial2.println("Front-Left RMS: " + String(leftFront_RMS));

	*/

	/*

	if (front > leftRight_RMS) return 'f';
	if (front < leftRight_RMS) return 'u'; // UTurn added, may arise problem
	if (left > (rightFront_RMS + 5.00)) return 'l'; // Both right and left have to outrun front sensor
	if (right > (leftFront_RMS + 5.00)) return 'r';
	if (!(front > leftRight_RMS) || )
	*/
	
	/*if (front > left && front > right) return 'f';
	if (front < right && front < left) return 'u';
	if (left > front && left > right) return 'l';
	if (right > front && right > left) return 'r';*/
}


void stop(int time)
{
	setMotors(0, 0);
	delay(time);
}


void loop()
{

	updateDistance();
	switch (decision())
	{

	case 'f':

		updateDistance();
		setMotors(speed, speed);
		if (left >= leftBoundMax){
			setMotors(speed - 60, speed);
		}
		if (left < leftBoundMin){
			setMotors(speed, speed - 60);
		}
		break;


	case 'l':
		updateDistance();
		setMotors(speed, speed);
		delay(400);
		setMotors(0, speed);
		delay(700);
		setMotors(speed, speed);
		delay(200);
		break;

	case 'r':
		updateDistance();
		setMotors(0, 0);
		delay(400);
		setMotors(speed, 0);
		delay(825); // Right Turn speed delay
		break;

	case 'u':
		Serial2.println("Uturn");
		updateDistance();
		setMotors(-50, -50);
		delay(5);
		setMotors(0, 0);
		delay(1000);
		setMotors(0, -200);
		delay(200);
		setMotors(0, 0);
		delay(1000);
		setMotors(speed, 0);
		delay(700);
		setMotors(0, 0);
		delay(1000);
		break;

	default:
		Serial2.println("No condition found");
		break; 
		}
	}



