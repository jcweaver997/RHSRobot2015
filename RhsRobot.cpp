#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Robot
#include "Drivetrain.h"
#include "RhsRobot.h"

RhsRobot::RhsRobot()
{
	Controller_1 = NULL;
	Controller_2 = NULL;
	drivetrain = NULL; 
	autonomous = NULL;
}

RhsRobot::~RhsRobot()
{
	/*
	 * Free all allocated memory
	 * EXAMPLE: delete drivetrain;
	 */

	delete Controller_1;
	delete Controller_2;
	delete autonomous;
	delete drivetrain;
}

void RhsRobot::Init()			//Initializes the robot
{
	/* 
	 * Set all pointers to null and then allocate memory and construct objects
	 * EXAMPLE:	drivetrain = NULL;
	 * 			drivetrain = new Drivetrain(this);
	 */

	Controller_1 = new Joystick(1);
	Controller_2 = new Joystick(2);
	drivetrain = new Drivetrain(); 
	autonomous = new Autonomous();
}

void RhsRobot::OnStateChange()			//Handles state changes
{
	/* 
	 * Alert all components of state changes by sending robotMessage.
	 * EXAMPLE:	if(drivetrain)
	 * 			{
	 * 				drivetrain->SendMessage(&robotMessage);
	 * 			}
	 */

	if(drivetrain)
	{
		drivetrain->SendMessage(&robotMessage);
	}

	if(autonomous)
	{
		autonomous->SendMessage(&robotMessage);
	}
}

void RhsRobot::Run()			//Robot logic
{	
	/* Poll for control data and send messages to each subsystem. Surround blocks with if(component) so entire components can be disabled
	 * by commenting out their construction.
	 * EXAMPLE: if(drivetrain) 
	 * 			{ 
	 * 				//Check joysticks and send messages 
	 * 			}
	 */

	if(autonomous)
	{
		if(GetCurrentRobotState() == ROBOT_STATE_AUTONOMOUS)
		{
			// all messages to components will come from the autonomous task
			return;
		}
	}

	if(drivetrain)
	{
		robotMessage.params.tankDrive.left = TANK_DRIVE_LEFT;
		robotMessage.params.tankDrive.right = TANK_DRIVE_RIGHT;
		drivetrain->SendMessage(&robotMessage);
	}
}

START_ROBOT_CLASS(RhsRobot)			//Spawns an instance of the RhsRobot class
