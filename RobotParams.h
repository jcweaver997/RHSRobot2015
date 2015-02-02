/* 
 * This header contains basic parameters for the robot. All parameters must be constants with internal
 * linkage, otherwise the One Definition Rule will be violated.
 */

#ifndef ROBOT_PARAMS_H
#define ROBOT_PARAMS_H

//Robot
#include "JoystickLayouts.h"			//For joystick layouts

//Robot Params
const char* const ROBOT_NAME =		"RhsRobot2015";			//Formal name
const char* const ROBOT_NICKNAME =   "Cybil";      			//Nickname
const char* const ROBOT_VERSION =	"-1.0.0-Alpha";			//Version

//Task Params - Defines component task priorites relative to the default priority.
//EXAMPLE: const int DRIVETRAIN_PRIORITY = DEFAULT_PRIORITY -2;
const int DEFAULT_PRIORITY = 0;
const int COMPONENT_PRIORITY = DEFAULT_PRIORITY;
const int DRIVETRAIN_PRIORITY = DEFAULT_PRIORITY;
const int AUTONOMOUS_PRIORITY = DEFAULT_PRIORITY;
const int AUTOEXEC_PRIORITY = DEFAULT_PRIORITY;
const int AUTOPARSER_PRIORITY = DEFAULT_PRIORITY;
const int CONVEYOR_PRIORITY = DEFAULT_PRIORITY;
const int CLICKER_PRIORITY = DEFAULT_PRIORITY;

//Task Names - Used when you view the task list but used by the operating system
//EXAMPLE: const char* DRIVETRAIN_TASKNAME = "tDrive";
const char* const COMPONENT_TASKNAME	= "tComponent";
const char* const DRIVETRAIN_TASKNAME	= "tDrive";
const char* const AUTONOMOUS_TASKNAME	= "tAuto";
const char* const AUTOEXEC_TASKNAME		= "tAutoEx";
const char* const AUTOPARSER_TASKNAME	= "tParse";
const char* const CONVEYOR_TASKNAME		= "tConveyor";
const char* const CLICKER_TASKNAME		= "tClicker";

//TODO change these variables throughout the code to PIPE instead  of QUEUE
//Queue Names - Used when you want to open the message queue for any task
//NOTE: 2015 - we use pipes instead of queues
//EXAMPLE: const char* DRIVETRAIN_TASKNAME = "tDrive";
const char* const COMPONENT_QUEUE 	= "/tmp/qComp";
const char* const DRIVETRAIN_QUEUE 	= "/tmp/qDrive";
const char* const AUTONOMOUS_QUEUE 	= "/tmp/qAuto";
const char* const AUTOPARSER_QUEUE 	= "/tmp/qParse";
const char* const CONVEYOR_QUEUE	= "/tmp/qConvey";
const char* const CLICKER_QUEUE	= "/tmp/qClicker";

//PWM Channels - Assigns names to PWM ports 1-10 on the Roborio
//EXAMPLE: const int PWM_DRIVETRAIN_FRONT_LEFT_MOTOR = 1;
const int PWM_DRIVETRAIN_LEFT_MOTOR = 1;
const int PWM_DRIVETRAIN_RIGHT_MOTOR = 0;

//CAN IDs - Assigns names to the various CAN IDs
//EXAMPLE: const int CAN_PDB = 42;
/* Pallet Jack motors
 * 1 - left
 * 2 - right
 * 3 - conveyor
 * 4 -
 * 5 -
 * 6 - lifter
 */
const int CAN_PDB = 42;
const int CAN_DRIVETRAIN_LEFT_MOTOR = 1;
const int CAN_DRIVETRAIN_RIGHT_MOTOR = 2;
const int CAN_PALLET_JACK_CONVEYOR = 3;
const int CAN_PALLET_JACK_INTAKE_VERTICAL_LEFT = 4;
const int CAN_PALLET_JACK_INTAKE_VERTICAL_RIGHT = 5;
const int CAN_PALLET_JACK_TOTE_LIFT = 6;
const int CAN_CUBE_CLICKER = 0;
const int CAN_CUBE_INTAKE = 0;
const int CAN_CUBE_BIN_LIFT = 0;

//Relay Channels - Assigns names to Relay ports 1-8 on the Roborio
//EXAMPLE: const int RLY_COMPRESSOR = 1;

//Digital I/O - Assigns names to Digital I/O ports 1-14 on the Roborio
//EXAMPLE: const int PWM_DRIVETRAIN_ENCODER_RIGHT_A = 1;

//Solenoid - Assigns names to Solenoid ports 1-8 on the 9403
//EXAMPLE: const int SOL_DRIVETRAIN_SOLENOID_SHIFT_IN = 1;

//I2C - Assigns names to I2C ports 1-2 on the Roborio
//EXAMPLE: const int IO2C_AUTO_ACCEL = 1;

//Analog I/O - Assigns names to Analog I/O ports 1-8 on Anal;og Breakout Module
//EXAMPLE: const int AIO_BATTERY = 8;

//Primary Controller Mapping - Assigns action to buttons or axes on the first joystick
#undef	USE_X3D_FOR_CONTROLLER_1
#undef	USE_XBOX_FOR_CONTROLLER_1
#define	USE_L310_FOR_CONTROLLER_1

//Secondary Controller Mapping - Assigns action to buttons or axes on the second joystick
#define	USE_X3D_FOR_CONTROLLER_2
#undef 	USE_XBOX_FOR_CONTROLLER_2
#undef USE_L310_FOR_CONTROLLER_2

#ifdef USE_XBOX_FOR_CONTROLLER_1
#define TANK_DRIVE_LEFT				-Controller_1->GetRawAxis(XBX_AXS_STCK_LFT_Y)
#define TANK_DRIVE_RIGHT			-Controller_1->GetRawAxis(XBX_AXS_STCK_RGHT_Y)
#endif

#ifdef USE_L310_FOR_CONTROLLER_1
#define TANK_DRIVE_LEFT				-Controller_1->GetRawAxis(L310_THUMBSTICK_LEFT_Y)
#define TANK_DRIVE_RIGHT			-Controller_1->GetRawAxis(L310_THUMBSTICK_RIGHT_Y)
#define CONVEYOR_FWD				Controller_1->GetRawButton(L310_BUTTON_BUMPER_LEFT)
#define CONVEYOR_BCK				Controller_1->GetRawButton(L310_BUTTON_BUMPER_RIGHT)
#endif

#ifdef USE_X3D_FOR_CONTROLLER_2
#endif

#ifdef USE_XBOX_FOR_CONTROLLER_2
#endif

#ifdef USE_L310_FOR_CONTROLLER_2
#endif
#endif //ROBOT_PARAMS_H
