/* 
 * In the RhsRobot Framework, each physical subsystem has a corresponding component class.
 * These component classes should inherit the ComponentBase class for access to functions that
 * all components use.
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>

//Local
#include "ComponentBase.h"

//Robot
class RhsRobot;
#include "RobotMessage.h"

ComponentBase::ComponentBase(const char* componentName, const char *queueName, int priority)
{	
	iLoop = 0;
	iPipeRcv = -1;
	iPipeXmt = -1;

	mkfifo(queueName, 0666);
	queueLocal = queueName;
}

void ComponentBase::SendMessage(RobotMessage* robotMessage)
{
	RobotMessage message = *robotMessage;

	if(iPipeXmt < 0)
	{
		iPipeXmt = open(queueLocal.c_str(), O_WRONLY);
		assert(iPipeXmt > 0);
	}

	write(iPipeXmt, (char*)&message, sizeof(RobotMessage));
}

void ComponentBase::ReceiveMessage()			//Receives a message and copies it into localMessage
{
	fd_set selectSet;
	struct timeval timeout;

	if(iPipeRcv < 0)
	{
		iPipeRcv = open(queueLocal.c_str(), O_RDONLY);
		assert(iPipeRcv > 0);
	}

	FD_ZERO(&selectSet);
	FD_SET(iPipeRcv, &selectSet);

	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;

	if(select(iPipeRcv + 1, &selectSet, NULL, NULL, &timeout) == 0)
	{
		localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
	}
	else
	{
		read(iPipeRcv, (char*)&localMessage, sizeof(RobotMessage));
	}
}

void ComponentBase::ClearMessages(void)
{
	RobotMessage eatMessage;
	
	// eat all the messages in the queue
	
	fcntl(iPipeRcv, F_SETFL, O_NONBLOCK);

	while(read(iPipeRcv, (char*)&eatMessage, sizeof(RobotMessage)) > 0)
	{
		// intentionally empty
	}

	fcntl(iPipeRcv, F_SETFL, 0);

	// make sure the localMessage is innocuous
	
	localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
}

void ComponentBase::DoWork()
{
	int iLast;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &iLast);

	while(true)
	{
		ReceiveMessage();		//Receives a message and copies it into localMessage

		if(localMessage.command == COMMAND_ROBOT_STATE_DISABLED ||			//Tests for state change messages
				localMessage.command == COMMAND_ROBOT_STATE_AUTONOMOUS ||
				localMessage.command == COMMAND_ROBOT_STATE_TELEOPERATED ||
				localMessage.command == COMMAND_ROBOT_STATE_TEST ||
				localMessage.command == COMMAND_ROBOT_STATE_UNKNOWN)
		{
			OnStateChange();			//Handles state changes
		}

		Run();			//Component logic
		iLoop++;
	}
}
