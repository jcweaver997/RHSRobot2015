/* 
 * The RhsRobotBase class is an extension to RobotBase and provides basic robot functionality.
 */

#include <assert.h>

//Built-In

#include "WPILib.h"			//For the RobotBase class, the watchdog, SmartDashboard, and the DriverStationLCD class

//Local
#include "RhsRobotBase.h"			//For the local header file

//Robot
#include "RobotParams.h"			//For various robot parameters
#include "Autonomous.h"

RhsRobotBase::RhsRobotBase()			//Constructor
{
	printf("\n\t\t%s \"%s\"\n\tVersion %s built %s at %s\n\n", ROBOT_NAME, ROBOT_NICKNAME, ROBOT_VERSION, __DATE__, __TIME__);

	previousRobotState = ROBOT_STATE_UNKNOWN;
	currentRobotState = ROBOT_STATE_UNKNOWN;
	//TODO call function to turn off watchdog
	SmartDashboard::init();
	loop = 0;			//Initializes the loop counter
}

RhsRobotBase::~RhsRobotBase()			//Destructor
{	
}

RobotOpMode RhsRobotBase::GetCurrentRobotState()			//Returns the current robot state
{
	return currentRobotState;
}

RobotOpMode RhsRobotBase::GetPreviousRobotState()			//Returns the previous robot state
{
	return previousRobotState;
}

bool RhsRobotBase::HasStateChanged()			//Returns if the robot state has just changed
{
	return (previousRobotState != currentRobotState);
}

int RhsRobotBase::GetLoop()			//Returns the loop number
{
	return loop;
}

void RhsRobotBase::StartCompetition()			//Robot's main function
{
	DriverStation *pDS = DriverStation::GetInstance();

	Init();		//Initialize the robot

	while(true)
	{
		if(!pDS->IsNewControlData())
		{
			usleep(1000);
			continue;
		}

		//Checks the current state of the robot
		if(IsDisabled())
		{
			currentRobotState = ROBOT_STATE_DISABLED;
		}
		else if(IsEnabled() && IsAutonomous())
		{
			currentRobotState = ROBOT_STATE_AUTONOMOUS;
		}
		else if(IsEnabled() && IsOperatorControl())
		{
			currentRobotState = ROBOT_STATE_TELEOPERATED;
		}
		else if(IsEnabled() && IsTest())
		{
			currentRobotState = ROBOT_STATE_TEST;
		}
		else
		{
			currentRobotState = ROBOT_STATE_UNKNOWN;
		}

		if(HasStateChanged())			//Checks for state changes
		{
			switch(GetCurrentRobotState())
			{
			case ROBOT_STATE_DISABLED:
				printf("ROBOT_STATE_DISABLED\n");
				robotMessage.command = COMMAND_ROBOT_STATE_DISABLED;
				break;
			case ROBOT_STATE_AUTONOMOUS:
				printf("ROBOT_STATE_AUTONOMOUS\n");
				robotMessage.command = COMMAND_ROBOT_STATE_AUTONOMOUS;
				break;
			case ROBOT_STATE_TELEOPERATED:
				printf("ROBOT_STATE_TELEOPERATED\n");
				robotMessage.command = COMMAND_ROBOT_STATE_TELEOPERATED;
				break;
			case ROBOT_STATE_TEST:
				printf("ROBOT_STATE_TEST\n");
				robotMessage.command = COMMAND_ROBOT_STATE_TEST;
				break;
			case ROBOT_STATE_UNKNOWN:
				printf("ROBOT_STATE_UNKNOWN\n");
				robotMessage.command = COMMAND_ROBOT_STATE_UNKNOWN;
				break;
			}

			OnStateChange();			//Handles the state change
		}

		if(IsEnabled())
		{
			if((currentRobotState == ROBOT_STATE_TELEOPERATED) || 
					(currentRobotState == ROBOT_STATE_TEST) ||
					(currentRobotState == ROBOT_STATE_AUTONOMOUS))
			{
				Run();			//Robot logic
			}
		}

		previousRobotState = currentRobotState;

		++loop;		//Increment the loop counter
	}
}
