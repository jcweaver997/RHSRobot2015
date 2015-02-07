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

	leftMotor = new CANTalon(CAN_DRIVETRAIN_LEFT_MOTOR);
	rightMotor = new CANTalon(CAN_DRIVETRAIN_RIGHT_MOTOR);
	wpi_assert(leftMotor && rightMotor);
	leftMotor->SetControlMode(CANSpeedController::kPercentVbus);
	rightMotor->SetControlMode(CANSpeedController::kPercentVbus);
	leftMotor->SetVoltageRampRate(120.0);
	rightMotor->SetVoltageRampRate(120.0);

	gyro = new ADXRS453Z;
	wpi_assert(gyro);
	gyro->Start();

	pTask = new Task(DRIVETRAIN_TASKNAME, (FUNCPTR) &Drivetrain::StartTask,
			DRIVETRAIN_PRIORITY, DRIVETRAIN_STACKSIZE);
	wpi_assert(pTask);
	pTask->Start((int)this);
}

Drivetrain::~Drivetrain()			//Destructor
{
	delete(pTask);
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

