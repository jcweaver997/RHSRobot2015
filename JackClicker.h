#ifndef JACKCLICKER_H
#define JACKCLICKER_H

#include <pthread.h>

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

class JackClicker : public ComponentBase
{
public:
	JackClicker();
	virtual ~JackClicker();
	static void *StartTask(void *pThis)
	{
		((JackClicker *)pThis)->DoWork();
		return(NULL);
	}

private:
	CANTalon *clickerMotor;

	//All Cube sensors are connected to the Talons, and are thus not
	// represented in the code.
	void OnStateChange();
	void Run();
};

#endif			//JACKCLICKER_H
