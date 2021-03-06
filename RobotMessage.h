/* 
 * The RobotMessage struct is a data structure used to pass information to the robot's components. It is composed of a command that
 * indicates the action ot be carried out and a union of params that contain additional data.
 */

#ifndef ROBOT_MESSAGE_H
#define ROBOT_MESSAGE_H

enum MessageCommand
{
	COMMAND_UNKNOWN,
	
	COMMAND_SYSTEM_MSGTIMEOUT,
	COMMAND_SYSTEM_OK,
	COMMAND_SYSTEM_ERROR,

	COMMAND_ROBOT_STATE_DISABLED,
	COMMAND_ROBOT_STATE_AUTONOMOUS,
	COMMAND_ROBOT_STATE_TELEOPERATED,
	COMMAND_ROBOT_STATE_TEST,
	COMMAND_ROBOT_STATE_UNKNOWN,

	COMMAND_AUTONOMOUS_RUN,
	COMMAND_CHECKLIST_RUN,

	COMMAND_DRIVETRAIN_DRIVE_TANK,

	COMMAND_CONVEYOR_RUN_FWD,
	COMMAND_CONVEYOR_RUN_BCK,
	COMMAND_CONVEYOR_STOP,
	COMMAND_CONVEYOR_INTAKELEFT_IN,
	COMMAND_CONVEYOR_INTAKELEFT_OUT,
	COMMAND_CONVEYOR_INTAKELEFT_STOP,
	COMMAND_CONVEYOR_INTAKERIGHT_IN,
	COMMAND_CONVEYOR_INTAKERIGHT_OUT,
	COMMAND_CONVEYOR_INTAKERIGHT_STOP,
	COMMAND_CONVEYOR_INTAKEBOTH_IN,
	COMMAND_CONVEYOR_INTAKEBOTH_OUT,
	COMMAND_CONVEYOR_INTAKEBOTH_STOP,
	COMMAND_CONVEYOR_RUNALL_FWD,
	COMMAND_CONVEYOR_RUNALL_BCK,
	COMMAND_CONVEYOR_RUNALL_STOP,

	COMMAND_JACKCLICKER_RAISE,
	COMMAND_JACKCLICKER_LOWER,
	COMMAND_JACKCLICKER_STOP,

	COMMAND_CUBECLICKER_RAISE,
	COMMAND_CUBECLICKER_LOWER,
	COMMAND_CUBECLICKER_STOP,
	COMMAND_CUBEINTAKE_RUN,
	COMMAND_CUBEINTAKE_STOP,
	COMMAND_CUBEAUTOCYCLE_START,
	COMMAND_CUBEAUTOCYCLE_STOP,

	COMMAND_CANLIFTER_RAISE,
	COMMAND_CANLIFTER_LOWER,
	COMMAND_CANLIFTER_STOP,

	COMMAND_COMPONENT_TEST,

	COMMAND_LAST
};

struct TankDriveParams
{
	float left;
	float right;
};

struct AutonomousParams
{
	unsigned uMode;
	unsigned uDelay;
};

union MessageParams
{
	TankDriveParams tankDrive;	
	AutonomousParams autonomous;
};

struct RobotMessage
{
	MessageCommand command;
	int replyQ;
	MessageParams params;
};

#endif //ROBOT_MESSAGE_H
