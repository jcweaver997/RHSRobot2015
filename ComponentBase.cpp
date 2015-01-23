/* 
 * In the RhsRobot Framework, each physical subsystem has a corresponding component class.
 * These component classes should inherit the ComponentBase class for access to functions that
 * all components use.
 */

#include <stdio.h>
#include <stddef.h>
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


    msgqID = socket(PF_LOCAL,SOCK_DGRAM,0);
    sock.sun_family = AF_UNIX;

    strcpy(sock.sun_path,' ' + queueName);
    sock.sun_path[0] = 0;

    sock_size = (offsetof (struct sockaddr_un, sun_path)
              + strlen (queueName) + 1);

    printf("About to bind to %s \n",queueName);
    int bind_err = bind(msgqID,(const sockaddr*) &sock,sock_size);

    printf("name is %s, msgqid = %08X, errno = %d\n", queueName, msgqID, bind_err);

    ClearMessages();    // start fresh, no stale messages
}

ComponentBase::~ComponentBase()
{
	pthread_cancel(taskID);
	close(msgqID);
}

void ComponentBase::SendMessage(RobotMessage* robotMessage)
{
	RobotMessage message = *robotMessage;
	sendto(msgqID, (char*)&message, sizeof(RobotMessage), 0, (sockaddr*)&sock, (uint)sock_size);
}

void ComponentBase::ReceiveMessage()			//Receives a message and copies it into localMessage
{
	struct timeval timeout;

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	//timeout.tv_usec = 500000;
	//timeout.tv_nsec = 50000000;

	fd_set queues;
	FD_ZERO(&queues);
	FD_SET(msgqID,&queues);

	int val = select(1,&queues,NULL,NULL,&timeout);

	if (val == 0 || val == -1)
	{
		localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
	}
	else
	{
		recvfrom(msgqID,(char*)&localMessage,sizeof(RobotMessage),0, (sockaddr*)&sock, (uint*)&sock_size);
	}
}

void ComponentBase::ClearMessages(void)
{
	RobotMessage eatMessage;
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	
	// eat all the messages in the queue
	fd_set queues;
	FD_ZERO(&queues);
	FD_SET(msgqID,&queues);

	while(1)
	{
		int val = select(1,&queues,NULL,NULL,&timeout);
		if (val != -1 && val != 1)
		{
			printf("Queue cleared!\n");
			break;
		}
		recvfrom(msgqID,(char*)&eatMessage,sizeof(RobotMessage),0, (sockaddr*)&sock, (uint*)&sock_size);
	}

	// make sure the localMessage is innocuous
	
	localMessage.command = COMMAND_SYSTEM_MSGTIMEOUT;
}

void ComponentBase::Task()			//The component's main function
{
	printf("calling init\n");
	Init();			//Initialize the component
	printf("Init done");
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
