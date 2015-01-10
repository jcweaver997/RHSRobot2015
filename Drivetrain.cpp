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


Drivetrain::Drivetrain()
: ComponentBase(DRIVETRAIN_TASKNAME, DRIVETRAIN_QUEUE, DRIVETRAIN_PRIORITY)
{
	fLastLeft = 0.0;
	fLastRight = 0.0;

	leftMotor = NULL;
	rightMotor = NULL;
};

Drivetrain::~Drivetrain()			//Destructor
{
	delete leftMotor;
	delete rightMotor;
};

void Drivetrain::Init()			//Initializes the drivetrain component
{
	leftMotor = new Victor(PWM_DRIVETRAIN_LEFT_MOTOR);
	rightMotor = new Victor(PWM_DRIVETRAIN_RIGHT_MOTOR);
};

void Drivetrain::OnStateChange()			//Handles state changes
{
	// reset the servos and stop the motors

	fLastLeft = 0.0;
	fLastRight = 0.0;


	switch(localMessage.command)
	{
		case COMMAND_ROBOT_STATE_AUTONOMOUS:
			break;

		case COMMAND_ROBOT_STATE_TEST:
			break;

		case COMMAND_ROBOT_STATE_TELEOPERATED:
			break;

		case COMMAND_ROBOT_STATE_DISABLED:
			break;

		case COMMAND_ROBOT_STATE_UNKNOWN:
			break;

		default:
			break;
	}
}

void Drivetrain::Run()
{
	switch(localMessage.command)
	{
		case COMMAND_DRIVETRAIN_DRIVE_TANK:
			TankDrive(pow(localMessage.params.tankDrive.left,3),
					pow(localMessage.params.tankDrive.right,3));
			break;

		case COMMAND_SYSTEM_MSGTIMEOUT:
		default:
			break;
	}
};

void Drivetrain::TankDrive(float left, float right)			//Drive with tank drive behavior
{
	if((left < JOYSTICK_DEADZONE) && (left > -JOYSTICK_DEADZONE))
	{
		// in the joystick dead zone

		left = 0.0;
	}
	else
	{
		// limit the amount of change is speed per message
		// so we don't destroy belts (or anything else)

		if((left - fLastLeft) > GAIN_PER_MESSAGE)
		{
			left = fLastLeft + GAIN_PER_MESSAGE;
		}
		else if((left - fLastLeft) < -GAIN_PER_MESSAGE)
		{
			left = fLastLeft - GAIN_PER_MESSAGE;
		}
	}


	if((right < JOYSTICK_DEADZONE) && (right > -JOYSTICK_DEADZONE))
	{
		// in the joystick dead zone

		right = 0.0;
	}
	else
	{
		if((right - fLastRight) > GAIN_PER_MESSAGE)
		{
			right = fLastRight + GAIN_PER_MESSAGE;
		}
		else if((right - fLastRight) < -GAIN_PER_MESSAGE)
		{
			right = fLastRight - GAIN_PER_MESSAGE;
		}
	}

	leftMotor->Set(-left);
	rightMotor->Set(right);
	fLastLeft = left;
	fLastRight = right;
};
