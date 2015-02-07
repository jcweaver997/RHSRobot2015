
#ifndef COMPONENT_H
#define COMPONENT_H

#include <pthread.h>

//Robot
#include "ComponentBase.h"			//For ComponentBase class

//WPILib
#include "WPILib.h"

class Component : public ComponentBase
{
public:
	Component();
	virtual ~Component();
	static void *StartTask(void *pThis)
	{
		((Component *)pThis)->DoWork();
		return(NULL);
	}

private:
	void OnStateChange();
	void Run();
};

#endif			//COMPONENT_H
