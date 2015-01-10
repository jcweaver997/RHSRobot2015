
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include <iostream>
#include <fstream>
#include <string>

#include "AutonomousBase.h"
#include "RobotParams.h"
#include "RobotMessage.h"

#include "WPILib.h"

class Autonomous : public AutonomousBase
{
	public:
		Autonomous();
		virtual ~Autonomous();

	private:
		void Evaluate(std::string rStatement);
};

#endif // AUTONOMOUS_H

