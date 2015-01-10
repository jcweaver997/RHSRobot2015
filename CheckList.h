/*
 * The CheckList class runs a prematch checklist
 */

#ifndef CHECKLIST_H
#define CHECKLIST_H

//Robot
#include "Drivetrain.h"
#include "ComponentBase.h"
class RhsRobot;

//WPILib
#include <WPILib.h>

class CheckList
{	
public:
	CheckList(RhsRobot* robot);
	~CheckList();
	void RunCheckList();

private:	
	RobotMessage localMessage;
};

#endif
