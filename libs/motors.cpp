#include "Arduino.h"
#include "motors.h"
#include "robot.h"


void Motors::init(){
	//Init input/output
	pinMode(MOTOR_RIGHT_1, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_RIGHT_2, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_RIGHT_IN, INPUT);   // sets the pin as output

	pinMode(MOTOR_LEFT_1, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_LEFT_2, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_LEFT_IN, INPUT);   // sets the pin as output
}


void Motors::setMotorRightFoward(){
	digitalWrite(MOTOR_RIGHT_1, HIGH);
	digitalWrite(MOTOR_RIGHT_2, LOW);
}

void Motors::setMotorRightBack(){
	digitalWrite(MOTOR_RIGHT_1, LOW);
	digitalWrite(MOTOR_RIGHT_2, HIGH);
}

void Motors::setMotorRightStop(){
	digitalWrite(MOTOR_RIGHT_1, LOW);
	digitalWrite(MOTOR_RIGHT_2, LOW);

}

void Motors::setMotorLeftFoward(){
	digitalWrite(MOTOR_LEFT_1, HIGH);
	digitalWrite(MOTOR_LEFT_2, LOW);
}

void Motors::setMotorLeftBack(){
	digitalWrite(MOTOR_LEFT_1, LOW);
	digitalWrite(MOTOR_LEFT_2, HIGH);
}

void Motors::setMotorLeftStop(){
	digitalWrite(MOTOR_LEFT_1, LOW);
	digitalWrite(MOTOR_LEFT_2, LOW);
}

void Motors::setFordward(){
	setMotorRightFoward();
	setMotorLeftFoward();
	checkSteps(STEPS, STEPS);

}

void Motors::setBack(){
	setMotorRightBack();
	setMotorLeftBack();
	checkSteps(STEPS, STEPS);

}

void Motors::setShortTurnLeft(){
	setMotorRightFoward();
	setMotorLeftBack();
	checkSteps(STEPS, STEPS);

}

void Motors::setLongTurnLeft(){
	setMotorRightFoward();
	setMotorLeftStop();
	checkSteps(STEPS, -1);


}

void Motors::Motors::setShortTurnRight(){
	setMotorRightBack();
	setMotorLeftFoward();
	checkSteps(STEPS, STEPS);


}

void Motors::Motors::setLongTurnRight(){
	setMotorRightStop();
	setMotorLeftFoward();
	checkSteps(0, STEPS);


}

void Motors::setStop(){
	setMotorRightStop();
	setMotorLeftStop();
}


void Motors::checkSteps(int motorRight, int motorLeft){
	int left;
	int right;
	int leftVal;
	int leftStoredVal;
	int rightVal;
	int rightStoredVal;

	left = 0;
	right = 0;
	leftStoredVal = HIGH;
	rightStoredVal = HIGH;

	while(true){
		if(left >= motorRight && left >= motorRight){
			setStop();
			break;
		} 
		if(left >= motorLeft){
			setMotorLeftStop();
		}
		if(right >= motorRight){
			setMotorRightStop();
		}
		
		leftVal = digitalRead(MOTOR_LEFT_IN); 
		if(leftVal!=leftStoredVal){
			leftStoredVal = leftVal;
			left++;
		}
		rightVal = digitalRead(MOTOR_RIGHT_IN); 
		if(rightVal!=rightStoredVal){
			rightStoredVal = rightVal;
			right++;
		}
		delay(10);

	}

}