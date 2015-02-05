/*
 * The Clicker component class handles both the Cube's tote lifting
 * and the intake roller.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Clicker.h"

Clicker::Clicker()
: ComponentBase(CLICKER_TASKNAME, CLICKER_QUEUE, CLICKER_PRIORITY)
{
	pthread_attr_t attr;
	taskID = 0;
	bEnableAutoCycle = false;

	// run the clicker motor in braking mode till it hits a limit switch

	clickerMotor = new CANTalon(CAN_CUBE_CLICKER);
	clickerMotor->SetVoltageRampRate(120.0);
	clickerMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	clickerMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	// run the intake motor unless a tote has broken the beam

	intakeMotor = new CANTalon(CAN_CUBE_INTAKE);
	intakeMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	printf("Starting %s thread listening to %s\n", CLICKER_TASKNAME,
			CLICKER_QUEUE);

	// set thread attributes to default values
    pthread_attr_init(&attr);
    // we do not wait for threads to exit
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // each thread has a unique scheduling algorithm
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&taskID, &attr, &Clicker::StartTask, this);
    pthread_setname_np(taskID, CLICKER_TASKNAME);

};

Clicker::~Clicker()
{
	pthread_cancel(taskID);
};

void Clicker::OnStateChange()
{
	switch (localMessage.command)
	{
		case COMMAND_ROBOT_STATE_AUTONOMOUS:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_TEST:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_TELEOPERATED:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_DISABLED:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_UNKNOWN:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		default:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;
	}
};

void Clicker::Run()
{
	switch(localMessage.command)			//Reads the message command
	{
		case COMMAND_CUBECLICKER_RAISE:
			clickerMotor->Set(0.10);		// the spring will help it up
			break;

		case COMMAND_CUBECLICKER_LOWER:
			clickerMotor->Set(-1.0);
			break;

		case COMMAND_CUBECLICKER_STOP:
			clickerMotor->Set(0.0);
			break;

		case COMMAND_CUBEINTAKE_RUN:
			intakeMotor->Set(1.0);
			break;

		case COMMAND_CUBEINTAKE_STOP:
			intakeMotor->Set(0.0);
			break;

		case COMMAND_CUBEAUTOCYCLE_START:
			bEnableAutoCycle = true;
			break;

		case COMMAND_CUBEAUTOCYCLE_STOP:
			bEnableAutoCycle = false;
			break;

		default:
			break;
		}

	//TODO: add timeout support for clicker motor just in case the sensors fail

	//TODO: add state machine for auto cycling

};
