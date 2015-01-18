/*
 * The Drivetrain component class handles driving related functionality.
 */

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

const float JOYSTICK_DEADZONE = 0.10;
const float GAIN_PER_MESSAGE = 0.1;

class Drivetrain : public ComponentBase
{
public:
	Drivetrain();
	~Drivetrain();

private:
	Victor* leftMotor;
	Victor* rightMotor;

	float fLastLeft;
	float fLastRight;

	int iLoop;

	void Init();
	void OnStateChange();
	void Run();

	void TankDrive(float left, float right);
};

#endif			//DRIVETRAIN_H
