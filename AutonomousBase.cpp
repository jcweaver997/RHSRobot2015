/*
 * The AutonomousBase component class handles basic autonomous functionallity.
 */

//Local
#include "AutonomousBase.h" 

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Built-In
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern "C" {

static void *RunAuto(void *pBase)
{
	((AutonomousBase *)pBase)->AutoTask();
	return(0);
};
}

AutonomousBase::AutonomousBase()
: ComponentBase(AUTONOMOUS_TASKNAME, AUTONOMOUS_QUEUE, AUTONOMOUS_PRIORITY)
{
	lineNumber = 0;
	bInAutoMode = false;
	iExecTaskID = -1;
}

AutonomousBase::~AutonomousBase()	//Destructor
{
}

void AutonomousBase::Init()	//Initializes the autonomous component
{
	LoadScriptFile();
}
 
void AutonomousBase::OnStateChange()	//Handles state changes
{
	pthread_attr_t attr;
	struct sched_param schedparam;

	if(localMessage.command == COMMAND_ROBOT_STATE_AUTONOMOUS)
	{
		// set thread attributes to default values
	    pthread_attr_init(&attr);
	    // we do not wait for threads to exit
	    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	    // each thread has a unique scheduling algorithm
	    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	    // we'll force the priority of threads or tasks
	    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	    // we'll use static real time priority levels
	    schedparam.__sched_priority = AUTOEXEC_PRIORITY;
	    pthread_attr_setschedparam(&attr, &schedparam);

	    pthread_create(&iExecTaskID, &attr, RunAuto, this);
	    pthread_setname_np(iExecTaskID, AUTOEXEC_TASKNAME);
	}	
	else if((localMessage.command == COMMAND_ROBOT_STATE_TELEOPERATED) ||
			(localMessage.command == COMMAND_ROBOT_STATE_DISABLED))
	{
		if(iExecTaskID > 0)
		{
			pthread_cancel(iExecTaskID);
			iExecTaskID = -1;
		}
	}
}

void AutonomousBase::Run()	//Autonomous logic
{
	switch(localMessage.command)
	{
		case COMMAND_AUTONOMOUS_RUN:
			if(lineNumber < AUTONOMOUS_SCRIPT_LINES)
			{
				if(script[lineNumber].empty() == false)
				{
					Evaluate(script[lineNumber]);
					++lineNumber;
				}
			}
			break;
		case COMMAND_CHECKLIST_RUN:
			if(lineNumber < AUTONOMOUS_CHECKLIST_LINES)
			{
				Evaluate(script[lineNumber]);
				++lineNumber;
			}
			break;

		default:
			break;
	}
}

void AutonomousBase::LoadScriptFile()
{
	ifstream scriptStream(AUTONOMOUS_SCRIPT_FILEPATH);
	
	if(scriptStream.is_open())
	{
		// don't read the script if executing it!
		
		if(bInAutoMode == false)
		{
			for(int i = 0; i < AUTONOMOUS_SCRIPT_LINES; ++i)
			{
				if(!scriptStream.eof())
				{
					getline(scriptStream, script[i]);
					cout << script[i] << endl;		
				}
				else
				{
					script[i].clear();
				}
			}
		}
		else
		{
			printf("Attempt to read script in auto mode\n");
		}

		scriptStream.close();
	}	
	else
	{
		printf("No auto file found\n");
	}
}

void AutonomousBase::AutoTask()
{
	lineNumber = 0;
	
	while(lineNumber < AUTONOMOUS_SCRIPT_LINES)
	{
		if(script[lineNumber].empty() == false)
		{
			Evaluate(script[lineNumber]);
			++lineNumber;
		}
	}
}
