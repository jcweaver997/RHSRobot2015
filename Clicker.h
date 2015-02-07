
#ifndef CLICKER_H
#define CLICKER_H

#include <pthread.h>

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

class Clicker : public ComponentBase
{
public:
	Clicker();
	virtual ~Clicker();
	static void *StartTask(void *pThis)
	{
		((Clicker *)pThis)->DoWork();
		return(NULL);
	}

private:
	CANTalon *clickerMotor;
	CANTalon *intakeMotor;
	bool bEnableAutoCycle;

	//All Cube sensors are connected to the Talons, and are thus not
	// represented in the code.
	void OnStateChange();
	void Run();
};

#endif			//CLICKER_H
