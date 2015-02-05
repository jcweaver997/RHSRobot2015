/*
 * The RhsRobot class is the main robot class. It inherits from RhsRobotBase and MUST define the Init() function, the Run() function, and
 * the OnStateChange() function.
 */

#ifndef RHS_ROBOT_H
#define RHS_ROBOT_H

#include "WPILib.h"
#include "RhsRobotBase.h"

//Robot
#include "Drivetrain.h"
#include "Autonomous.h"
#include "Conveyor.h"
#include "Clicker.h"
#include "JackClicker.h"
#include "CanLifter.h"

class RhsRobot : public RhsRobotBase
{
public:
	RhsRobot();
	virtual ~RhsRobot();

private:
	Joystick* Controller_1;
	Joystick* Controller_2;
	Drivetrain* drivetrain;
	Autonomous* autonomous;
	Conveyor* conveyor;
	Clicker* clicker;
	JackClicker* jackclicker;
	CanLifter* canlifter;
	
	void Init();
	void OnStateChange();
	void Run();

	int iLoop;
};

#endif //RHS_ROBOT_H
