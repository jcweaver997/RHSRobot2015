#ifndef CANLIFTER_H
#define CANLIFTER_H

#include <pthread.h>

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

class CanLifter : public ComponentBase
{
public:
	CanLifter();
	virtual ~CanLifter();
	static void *StartTask(void *pThis)
	{
		((CanLifter *)pThis)->DoWork();
		return(NULL);
	}

private:
	CANTalon *lifterMotor;

	//All Cube sensors are connected to the Talons, and are thus not
	// represented in the code.
	void OnStateChange();
	void Run();
};

#endif			//CANLIFTER_H
