
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
<<<<<<< HEAD
	enum ClickerState{
		STATE_CUBECLICKER_RAISE,
		STATE_CUBECLICKER_LOWER,
		STATE_CUBECLICKER_TOP,
		STATE_CUBECLICKER_BOTTOM
	};

	pthread_t taskID;
=======
>>>>>>> 6b48a868a32f3b5fc31c34acdaa49d65d461d6a0
	CANTalon *clickerMotor;
	CANTalon *intakeMotor;
	bool bEnableAutoCycle;
	bool hitTop;
	bool hitBottom;
	ClickerState LastState = STATE_CUBECLICKER_TOP;
	int NumOfTotes = 1;
	int LastChecked;
	//All Cube sensors are connected to the Talons, and are thus not
	// represented in the code.
	void OnStateChange();
	void Run();
	void Top();
	void Bottom();
	void Lower();
	void Raise();
};

#endif			//CLICKER_H
