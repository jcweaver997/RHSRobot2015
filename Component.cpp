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
	pTask = new Task(COMPONENT_TASKNAME, (FUNCPTR) &Component::StartTask,
			COMPONENT_PRIORITY, COMPONENT_STACKSIZE);
	wpi_assert(pTask);
	pTask->Start((int)this);
};

Component::~Component()
{
	delete(pTask);
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
