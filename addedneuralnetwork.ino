#include <NewPing/Newping.h>

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
}

char decision()
{
	if (front > left && front > right) return 'f';
	else if (left > front && left > right) return 'l';
	else if (right > front && right > left) return 'r';
}




void loop()
{
	updateDistance();
	switch (decision())
	{
	case 'f':
		updateDistance();
		if (front > min && left < front && right < front){
			if (left > leftBoundMin && left < leftBoundMax){
				setMotors(speed, speed);
			}
			if (left >= leftBoundMax){
				setMotors(speed - 60, speed);
			}
			if (left < leftBoundMin){
				setMotors(speed, speed - 60);
			}
	case 'l':
		updateDistance();
		if (left > 17 && front > min){
			setMotors(speed, speed);
			delay(400);
			setMotors(0, speed);
			delay(700);
			setMotors(speed, speed);
			delay(200);

		}
	case 'r':
		updateDistance();
		if (front < min && right > 17 && (left < leftBoundMax || left > leftBoundMin)){
			setMotors(0, 0);
			delay(400);
			setMotors(speed, 0);
			delay(825); // Right Turn speed delay
		}

		}
	}
}


