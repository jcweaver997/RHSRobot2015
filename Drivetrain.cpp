/*
 * The Drivetrain component class handles driving related functionality.
 */

//Local
#include "Drivetrain.h"			//For the local header file

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Built-In
#include <math.h>
#include <assert.h>

#include <string>
#include <iostream>
using namespace std;

Drivetrain::Drivetrain() :
		ComponentBase(DRIVETRAIN_TASKNAME, DRIVETRAIN_QUEUE,
				DRIVETRAIN_PRIORITY) {
	pthread_attr_t attr;
	int iError;

	taskID = 0;
	leftMotor = new CANTalon(CAN_DRIVETRAIN_LEFT_MOTOR);
	rightMotor = new CANTalon(CAN_DRIVETRAIN_RIGHT_MOTOR);
	leftMotor->SetControlMode(CANSpeedController::kPercentVbus);
	rightMotor->SetControlMode(CANSpeedController::kPercentVbus);
	leftMotor->SetVoltageRampRate(120.0);
	rightMotor->SetVoltageRampRate(120.0);


	assert(leftMotor && rightMotor);

	// set thread attributes to default values
	pthread_attr_init(&attr);
	// we do not wait for threads to exit
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	// each thread has a unique scheduling algorithm
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	printf("Starting %s thread listening to %s\n", DRIVETRAIN_TASKNAME,
			DRIVETRAIN_QUEUE);

	iError = pthread_create(&taskID, &attr, &Drivetrain::StartTask, this);

	if (iError) {
		printf("pthread_create: error = %d\n", iError);
		assert(iError == 0);
	}
	pthread_setname_np(taskID, DRIVETRAIN_TASKNAME);
}

Drivetrain::~Drivetrain()			//Destructor
{
	pthread_cancel(taskID);

	delete leftMotor;
	delete rightMotor;
}

void Drivetrain::OnStateChange()			//Handles state changes
{
	switch (localMessage.command) {
	case COMMAND_ROBOT_STATE_AUTONOMOUS:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_TEST:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_TELEOPERATED:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_DISABLED:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_UNKNOWN:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;

	default:
		leftMotor->Set(0.0);
		rightMotor->Set(0.0);
		break;
	}
}

void Drivetrain::Run() {
	switch (localMessage.command) {
	case COMMAND_DRIVETRAIN_DRIVE_TANK:
		leftMotor->Set(pow(localMessage.params.tankDrive.left, 3));
		rightMotor->Set(-pow(localMessage.params.tankDrive.right, 3));
		break;

	case COMMAND_SYSTEM_MSGTIMEOUT:
	default:
		break;
	}
}

