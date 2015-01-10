/*
 * The Drivetrain component class handles driving related functionality.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Component.h"

extern "C" {
int iNetConsoleTest;
} 

Component::Component()
: ComponentBase(COMPONENT_TASKNAME, COMPONENT_QUEUE, COMPONENT_PRIORITY)
{
};

Component::~Component()
{
};

void Component::Init()
{
};

void Component::OnStateChange()	
{
};

void Component::Run()
{
	//SmartDashboard::PutNumber("Component Test  ", iNetConsoleTest);

	switch(localMessage.command)			//Reads the message command
	{
		case COMMAND_COMPONENT_TEST:
			iNetConsoleTest++;
			break;

		default:
			break;
		}
};
