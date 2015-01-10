/* 
 * The RhsRobotBase class is an extension to RobotBase and provides basic robot functionality.
 */

#ifndef RHS_ROBOT_BASE_H
#define RHS_ROBOT_BASE_H

#include <unistd.h>

//Robot
#include "RobotMessage.h"

//WPILib
#include <WPILib.h>			//For the RobotBase class

typedef enum eRobotOpMode
{
	ROBOT_STATE_DISABLED,
	ROBOT_STATE_AUTONOMOUS,
	ROBOT_STATE_TELEOPERATED,
	ROBOT_STATE_TEST,
	ROBOT_STATE_UNKNOWN
} RobotOpMode;

class RhsRobotBase : public RobotBase
{
public:
	RhsRobotBase();				//Constructor
	virtual ~RhsRobotBase();			//Destructor

	RobotOpMode GetCurrentRobotState();			//Returns the current robot state
	RobotOpMode GetPreviousRobotState();			//Returns the previous robot state
	bool HasStateChanged();			//Returns if the robot state has just changed

	int GetLoop();			//Returns the loop number

protected:
	RobotMessage robotMessage;			//Message to be written and sent to components

	virtual void Init() = 0;			//Abstract function: initializes the robot
	virtual void OnStateChange() = 0;			//Abstract function: handles state changes
	virtual void Run() = 0;			//Abstract function: robot logic

private:
	RobotOpMode currentRobotState;			//Current robot state
	RobotOpMode previousRobotState;			//Previous robot state

	int loop;			//Loop counter

	void StartCompetition();			//Robot's main function
};

#endif //RHS_ROBOT_BASE_H
