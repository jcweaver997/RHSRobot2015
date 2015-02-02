/*
 * The Conveyor component class handles the Pallet Jack's tote intake and output.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Conveyor.h"

Conveyor::Conveyor() :
		ComponentBase(CONVEYOR_TASKNAME, CONVEYOR_QUEUE,
				CONVEYOR_PRIORITY) {
	pthread_attr_t attr;
	taskID = 0;

	conveyorMotor = new CANTalon(CAN_PALLET_JACK_CONVEYOR);
	conveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	//conveyorMotor->SetVoltageRampRate(24.0);

	// set thread attributes to default values
	pthread_attr_init(&attr);
	// we do not wait for threads to exit
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	// each thread has a unique scheduling algorithm
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	// we'll force the priority of threads or tasks
	//pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	// we'll use static real time priority levels
	//schedparam.sched_priority = priority;
	//pthread_attr_setschedparam(&attr, &schedparam);

	printf("Starting %s thread listening to %s\n", CONVEYOR_TASKNAME,
			DRIVETRAIN_QUEUE);

	pthread_create(&taskID, &attr, &Conveyor::StartTask, this);
	pthread_setname_np(taskID, CONVEYOR_TASKNAME);
}


Conveyor::~Conveyor() {
	pthread_cancel(taskID);
}

void Conveyor::OnStateChange() {
	switch (localMessage.command) {
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

void Conveyor::Run() {
	switch (localMessage.command)			//Reads the message command
	{
	case COMMAND_CONVEYOR_RUN_FWD:
		conveyorMotor->Set(1.0);
		break;
	case COMMAND_CONVEYOR_RUN_BCK:
		conveyorMotor->Set(-1.0);
		break;
	case COMMAND_CONVEYOR_STOP:
		conveyorMotor->Set(0.0);
		break;

	case COMMAND_SYSTEM_MSGTIMEOUT:
	default:
		break;
	}
}

