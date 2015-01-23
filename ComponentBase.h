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
#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>

//Robot
#include "RobotMessage.h"			//For the RobotMessage struct

class ComponentBase
{
public:
	ComponentBase(const char* componentName, const char *queueName, int priority);
	~ComponentBase();

	void Task();
	void SendMessage(RobotMessage* robotMessage);
	void ClearMessages();

	char* GetComponentName();
	mqd_t GetMessageQueueID() { return(msgqID); };
	pthread_t GetTaskID() { return(taskID); };
	int GetLoop() { return(iLoop); };

protected:
	RobotMessage localMessage;
	

	virtual void Init() { printf("base\n"); }			//Abstract function: initializes the component
	virtual void OnStateChange() = 0;	//Abstract function: handles state changes
	virtual void Run() = 0;				//Abstract function: component logic

private:
	char* componentName;
	mqd_t msgqID;
	pthread_t taskID;
	int iLoop;
	sockaddr_un sock;
	int sock_size;

	void ReceiveMessage();
};

#endif //COMPONENT_BASE_H
