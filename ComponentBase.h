/* 
 * In the RhsRobot Framework, each physical subsystem has a corresponding component class.
 * These component classes should inherit the ComponentBase class for access to functions that
 * all components use.
 */

#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include <pthread.h>		 /* for pthread calls */
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <time.h>			 /* for timeout structure */
#include <errno.h>
#include <mqueue.h>		     /* for POSIX message queues */

#include <string>
#include <iostream>
using namespace std;

#include "WPILib.h"

//Robot
#include "RobotMessage.h"			//For the RobotMessage struct

class ComponentBase
{
public:
	ComponentBase(const char* componentName, const char *queueName, int priority);
	virtual ~ComponentBase() {};

	void DoWork();
	void SendMessage(RobotMessage* robotMessage);
	void ClearMessages();

	char* GetComponentName();
	int GetLoop() { return(iLoop); };

protected:
	Task *pTask;
	RobotMessage localMessage;
	int iLoop;
	
	virtual void OnStateChange() = 0;
	virtual void Run() = 0;

private:
	char* componentName;
	string queueLocal;
	int iPipeRcv;
	int iPipeXmt;

	void ReceiveMessage();
};

#endif //COMPONENT_BASE_H
