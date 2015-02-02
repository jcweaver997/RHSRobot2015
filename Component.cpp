/*
 * The Drivetrain component class handles driving related functionality.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Component.h"

Component::Component()
: ComponentBase(COMPONENT_TASKNAME, COMPONENT_QUEUE, COMPONENT_PRIORITY)
{
	pthread_attr_t attr;
	taskID = 0;

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

    pthread_create(&taskID, &attr, &Component::StartTask, this);
    pthread_setname_np(taskID, COMPONENT_TASKNAME);

};

Component::~Component()
{
	pthread_cancel(taskID);
};

void Component::OnStateChange()	
{
};

void Component::Run()
{
	switch(localMessage.command)			//Reads the message command
	{
		case COMMAND_COMPONENT_TEST:
			break;

		default:
			break;
		}
};
