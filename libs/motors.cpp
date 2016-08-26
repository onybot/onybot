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
}

void Motors::setBack(){
	setMotorRightBack();
	setMotorLeftBack();
}

void Motors::setShortTurnLeft(){
	setMotorRightFoward();
	setMotorLeftBack();

}

void Motors::setLongTurnLeft(){
	setMotorRightFoward();
	setMotorLeftStop();

}

void Motors::Motors::setShortTurnRight(){
	setMotorRightBack();
	setMotorLeftFoward();

}

void Motors::Motors::setLongTurnRight(){
	setMotorRightStop();
	setMotorLeftFoward();

}

void Motors::setStop(){
	setMotorRightStop();
	setMotorLeftStop();
}


void Motors::steps(){
	int i;
	int leftVal;
	int storedVal;
	setStop();
	
	storedVal = HIGH;
	i = 0;
	setMotorLeftFoward();
	while(i<20){
		leftVal = digitalRead(MOTOR_LEFT_IN); 
		if(leftVal!=storedVal){
			storedVal = leftVal;
			i++;
		}
		delay(10);
	}
	setMotorLeftStop();
	delay(1000);
}