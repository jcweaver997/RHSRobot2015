/* 
 * In the RhsRobot Framework, each physical subsystem has a corresponding component class.
 * These component classes should inherit the ComponentBase class for access to functions that
 * all components use.
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

//Local
#include "ComponentBase.h"

//Robot
class RhsRobot;
#include "RobotMessage.h"


extern "C" {
static void *StartTask(void *pComponentBase)
{
	((ComponentBase *)pComponentBase)->Task();
	return(0);
}
}

ComponentBase::ComponentBase(const char* componentName, const char *queueName, int priority)			//Constructor
{	
	pthread_attr_t attr;
	//struct sched_param schedparam;

	struct mq_attr base_msg_attr;

	int iError;

	iLoop = 0;
	taskID = 0;

	// set thread attributes to default values
    pthread_attr_init(&attr);
    // we do not wait for threads to exit
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // each thread has a unique scheduling algorithm
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    // we'll force the priority of threads or tasks
    //pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    // we'll use static real time priority levels
    //schedparam.sched_priority = priority;
    //pthread_attr_setschedparam(&attr, &schedparam);

    printf("Starting %s thread listening to %s queue\n", componentName, queueName);

    iError = pthread_create(&taskID, &attr, StartTask, this);

	if(iError)
	{
		printf("pthread_create: error = %d\n", iError);
    	assert(iError == 0);
    }

    pthread_setname_np(taskID, componentName);

    base_msg_attr.mq_flags = 0;
    base_msg_attr.mq_maxmsg = 10;
    base_msg_attr.mq_msgsize = sizeof(struct RobotMessage);
    base_msg_attr.mq_curmsgs = 0;
    msgqID = mq_open(queueName, O_CREAT | O_RDWR, 0666, &base_msg_attr);
    printf("name is %s, msgqid = %08X, errno = %d\n", queueName, msgqID, errno);

    ClearMessages();    // start fresh, no stale messages
}

ComponentBase::~ComponentBase()
{
	pthread_cancel(taskID);
	mq_close(msgqID);
}

void ComponentBase::SendMessage(RobotMessage* robotMessage)
{
	RobotMessage message = *robotMessage;

	mq_send(msgqID, (char*)&message, sizeof(RobotMessage), 0);
}

void ComponentBase::ReceiveMessage()			//Receives a message and copies it into localMessage
{
	unsigned uMsgPriority;
	struct timespec timeout;

	timeout.tv_sec = 0;
	timeout.tv_nsec = 50000000;

	if(mq_timedreceive(msgqID, (char*)&localMessage, sizeof(RobotMessage),
		&uMsgPriority, &timeout) == ETIMEDOUT)
	{
		localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
	}
}

void ComponentBase::ClearMessages(void)
{
	RobotMessage eatMessage;
	unsigned uMsgPriority;
	struct timespec timeout;

	timeout.tv_sec = 0;
	timeout.tv_nsec = 0;
	
	// eat all the messages in the queue
	
	while(1)
	{
		if(mq_timedreceive(msgqID, (char*)&eatMessage, sizeof(RobotMessage),
			&uMsgPriority, &timeout) == ETIMEDOUT)
		{
			break;
		}
	}

	// make sure the localMessage is innocuous
	
	localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
}

void ComponentBase::Task()			//The component's main function
{
	printf("calling init\n");
	Init();			//Initialize the component

	while(true)
	{
		ReceiveMessage();		//Receives a message and copies it into localMessage

		if(localMessage.command == COMMAND_ROBOT_STATE_DISABLED ||			//Tests for state change messages
				localMessage.command == COMMAND_ROBOT_STATE_AUTONOMOUS ||
				localMessage.command == COMMAND_ROBOT_STATE_TELEOPERATED ||
				localMessage.command == COMMAND_ROBOT_STATE_TEST ||
				localMessage.command == COMMAND_ROBOT_STATE_UNKNOWN)
		{
			printf("calling OnStateChange\n");

			OnStateChange();			//Handles state changes
		}

		Run();			//Component logic
		iLoop++;
	}
}
