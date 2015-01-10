/***
This file contains our autonomous algorithms.  It should detect if we are in 
autonomous mode or not, select an algorithm based upon switch settings at
the driver station and implement the behaviours till autonomous mode ends.
 ***/

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Autonomous.h"
#include "AutoParser.h"


extern "C" {
}

Autonomous::Autonomous() : AutonomousBase()
{
}

Autonomous::~Autonomous()
{	
}



