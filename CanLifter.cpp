/*
 * The CanLifter component class handles the cube's can lifting
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "CanLifter.h"

CanLifter::CanLifter()
: ComponentBase(CANLIFTER_TASKNAME, CANLIFTER_QUEUE, CANLIFTER_PRIORITY)
{
	pthread_attr_t attr;
	taskID = 0;

	lifterMotor = new CANTalon(CAN_CUBE_BIN_LIFT);
	lifterMotor->SetVoltageRampRate(120.0);
	lifterMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	lifterMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	printf("Starting %s thread listening to %s\n", CANLIFTER_TASKNAME,
			CANLIFTER_QUEUE);

	// set thread attributes to default values
    pthread_attr_init(&attr);
    // we do not wait for threads to exit
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // each thread has a unique scheduling algorithm
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&taskID, &attr, &CanLifter::StartTask, this);
    pthread_setname_np(taskID, CANLIFTER_TASKNAME);

};

CanLifter::~CanLifter()
{
	pthread_cancel(taskID);
};

void CanLifter::OnStateChange()
{
	switch (localMessage.command)
	{
		case COMMAND_ROBOT_STATE_AUTONOMOUS:
			lifterMotor->Set(0.0);
			break;

		case COMMAND_ROBOT_STATE_TEST:
			lifterMotor->Set(0.0);
			break;

		case COMMAND_ROBOT_STATE_TELEOPERATED:
			lifterMotor->Set(0.0);
			break;

		case COMMAND_ROBOT_STATE_DISABLED:
			lifterMotor->Set(0.0);
			break;

		case COMMAND_ROBOT_STATE_UNKNOWN:
			lifterMotor->Set(0.0);
			break;

		default:
			lifterMotor->Set(0.0);
			break;
	}
};

void CanLifter::Run()
{
	switch(localMessage.command)
	{
		case COMMAND_CANLIFTER_RAISE:
			lifterMotor->Set(1.0);
			break;

		case COMMAND_CANLIFTER_LOWER:
			lifterMotor->Set(-1.0);
			break;

		case COMMAND_CANLIFTER_STOP:
			lifterMotor->Set(0.0);
			break;

		default:
			break;
		}

	//TODO: add timeout support for lifter motor just in case the sensors fail


};
