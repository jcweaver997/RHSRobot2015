/*
 * The AutonomousBase component class handles basic autonomous functionality.
 */

#ifndef AUTONOMOUS_BASE_H
#define AUTONOMOUS_BASE_H

//Robot
#include "ComponentBase.h" //For the ComponentBase class
#include "RobotParams.h" //For various robot parameters

//Built-In
#include <string>
#include <pthread.h>

const int AUTONOMOUS_SCRIPT_LINES = 64;
const int AUTONOMOUS_CHECKLIST_LINES = 64;
const char* const AUTONOMOUS_SCRIPT_FILEPATH = "RhsScript.txt";

class AutonomousBase : public ComponentBase
{
public:
	AutonomousBase();
	~AutonomousBase();
	void AutoTask();

protected:
	virtual void Evaluate(std::string statement) = 0;	//Evaluates an autonomous script statement
	RobotMessage Message;		//Struct to form messages to other tasks
	bool bInAutoMode;

private:
	std::string script[AUTONOMOUS_SCRIPT_LINES];	//Autonomous script
	int lineNumber;	//Current line number
	pthread_t iExecTaskID;
	
	void Init();	//Initializes the autonomous component
	void OnStateChange();	//Handles state changes
	void Run();	//Autonomous logic
	void LoadScriptFile();
};

#endif //AUTONOMOUS_BASE_H
