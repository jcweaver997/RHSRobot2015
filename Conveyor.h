
#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <pthread.h>

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

class Conveyor: public ComponentBase
{
public:
	Conveyor();
	virtual ~Conveyor();
	static void *StartTask(void *pThis)
	{
		((Conveyor*)pThis)->Task();
		return(NULL);
	}

private:
	pthread_t taskID;
	CANTalon *conveyorMotor;
	void OnStateChange();
	void Run();
};

#endif			//CONVEYOR_H
