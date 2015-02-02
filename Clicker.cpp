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

	clickerMotor = new CANTalon(CAN_CUBE_CLICKER);
	intakeMotor = new CANTalon(CAN_CUBE_INTAKE);

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

    pthread_create(&taskID, &attr, &Clicker::StartTask, this);
    pthread_setname_np(taskID, CLICKER_TASKNAME);

};

Clicker::~Clicker()
{
	pthread_cancel(taskID);
};

void Clicker::OnStateChange()
{
};

void Clicker::Run()
{
	switch(localMessage.command)			//Reads the message command
	{
		case COMMAND_CLICKER_RAISE:
			//TODO: add clicker raise, intake start
			break;
		case COMMAND_CLICKER_LOWER:
			//TODO: add clicker lower, intake stop
			break;

		default:
			break;
		}
};
