#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Robot
#include "RhsRobot.h"

RhsRobot::RhsRobot()
{
	Controller_1 = NULL;
	Controller_2 = NULL;
	drivetrain = NULL; 
	autonomous = NULL;
	conveyor = NULL;
    clicker = NULL;
    jackclicker = NULL;
    canlifter = NULL;

	iLoop = 0;
}

RhsRobot::~RhsRobot()
{
	/*
	 * Free all allocated memory
	 * EXAMPLE: delete drivetrain;
	 */

	delete Controller_1;
	delete Controller_2;
	//delete autonomous;
	delete drivetrain;
	delete conveyor;
	delete clicker;
	delete jackclicker;
	delete canlifter;
}

void RhsRobot::Init()			//Initializes the robot
{
	/* 
	 * Set all pointers to null and then allocate memory and construct objects
	 * EXAMPLE:	drivetrain = NULL;
	 * 			drivetrain = new Drivetrain();
	 */
	Controller_1 = new Joystick(0);
	Controller_2 = new Joystick(1);
	drivetrain = new Drivetrain(); 
	conveyor = new Conveyor();
	clicker = new Clicker();
	jackclicker = new JackClicker();
	canlifter = new CanLifter();
	//autonomous = new Autonomous();
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

	if(conveyor)
	{
		conveyor->SendMessage(&robotMessage);
	}

	if(clicker)
	{
		clicker->SendMessage(&robotMessage);
	}

	if(jackclicker)
	{
		jackclicker->SendMessage(&robotMessage);
	}

	if(canlifter)
	{
		canlifter->SendMessage(&robotMessage);
	}
}

void RhsRobot::Run()
{	
	//SmartDashboard::PutString("ROBOT STATUS", "Running");
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
		robotMessage.command = COMMAND_DRIVETRAIN_DRIVE_TANK;
		robotMessage.params.tankDrive.left = TANK_DRIVE_LEFT;
		robotMessage.params.tankDrive.right = TANK_DRIVE_RIGHT;
		drivetrain->SendMessage(&robotMessage);
	}

	if(conveyor)
	{
		if(CONVEYOR_FWD)
		{
			robotMessage.command = COMMAND_CONVEYOR_RUNALL_FWD;
		}
		else if(CONVEYOR_BCK)
		{
			robotMessage.command = COMMAND_CONVEYOR_RUNALL_BCK;
		}
		else
		{
			robotMessage.command = COMMAND_CONVEYOR_RUNALL_STOP;
		}

		conveyor->SendMessage(&robotMessage);
	}

	if(clicker)
	{
		//robotMessage.command = COMMAND_CUBEAUTOCYCLE_START;
		//clicker->SendMessage(&robotMessage);

		// Not much room for clicker control with single L310
		//TODO: assign input controls to the clicker
	}

	if(jackclicker)
	{
		//TODO: assign input controls to the pallet jack clicker
	}

	if(canlifter)
	{
		//TODO: assign input controls to the cube can lifter
	}

	iLoop++;
}

START_ROBOT_CLASS(RhsRobot)
