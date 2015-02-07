/*
 * The Conveyor component class handles the Pallet Jack's tote intake and output.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Conveyor.h"

Conveyor::Conveyor() :
		ComponentBase(CONVEYOR_TASKNAME, CONVEYOR_QUEUE,
				CONVEYOR_PRIORITY) {
	conveyorMotor = new CANTalon(CAN_PALLET_JACK_CONVEYOR);
	wpi_assert(conveyorMotor);
	conveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	conveyorMotor->SetVoltageRampRate(120.0);
	conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	intakeLeftMotor = new CANTalon(CAN_PALLET_JACK_INTAKE_VERTICAL_LEFT);
	wpi_assert(intakeLeftMotor);
	intakeLeftMotor->SetControlMode(CANSpeedController::kPercentVbus);

	intakeRightMotor = new CANTalon(CAN_PALLET_JACK_INTAKE_VERTICAL_RIGHT);
	wpi_assert(intakeRightMotor);
	intakeRightMotor->SetControlMode(CANSpeedController::kPercentVbus);

	pTask = new Task(CONVEYOR_TASKNAME, (FUNCPTR) &Conveyor::StartTask,
			CONVEYOR_PRIORITY, CONVEYOR_STACKSIZE);
	wpi_assert(pTask);
	pTask->Start((int)this);
}

Conveyor::~Conveyor() {
	delete(pTask);
}

void Conveyor::OnStateChange() {
	switch (localMessage.command) {
	case COMMAND_ROBOT_STATE_AUTONOMOUS:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_TEST:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_TELEOPERATED:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_DISABLED:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_ROBOT_STATE_UNKNOWN:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	default:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;
	}
}

void Conveyor::Run() {
	switch (localMessage.command)			//Reads the message command
	{
	case COMMAND_CONVEYOR_RUN_FWD:
		conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
		conveyorMotor->Set(1.0);
		break;
	case COMMAND_CONVEYOR_RUN_BCK:
		conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);
		conveyorMotor->Set(-1.0);
		break;
	case COMMAND_CONVEYOR_STOP:
		conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);
		conveyorMotor->Set(0.0);
		break;

	case COMMAND_CONVEYOR_INTAKELEFT_IN:
		intakeLeftMotor->Set(1.0);
		break;

	case COMMAND_CONVEYOR_INTAKELEFT_OUT:
		intakeLeftMotor->Set(-1.0);
		break;

	case COMMAND_CONVEYOR_INTAKELEFT_STOP:
		intakeLeftMotor->Set(0.0);
		break;

	case COMMAND_CONVEYOR_INTAKERIGHT_IN:
		intakeRightMotor->Set(-1.0);
		break;

	case COMMAND_CONVEYOR_INTAKERIGHT_OUT:
		intakeRightMotor->Set(1.0);
		break;

	case COMMAND_CONVEYOR_INTAKERIGHT_STOP:
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_CONVEYOR_INTAKEBOTH_IN:
		intakeLeftMotor->Set(1.0);
		intakeRightMotor->Set(-1.0);
		break;

	case COMMAND_CONVEYOR_INTAKEBOTH_OUT:
		intakeLeftMotor->Set(-0.0);
		intakeRightMotor->Set(1.0);
		break;

	case COMMAND_CONVEYOR_INTAKEBOTH_STOP:
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_CONVEYOR_RUNALL_FWD:
		conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
		conveyorMotor->Set(1.0);
		intakeLeftMotor->Set(1.0);
		intakeRightMotor->Set(-1.0);
		break;

	case COMMAND_CONVEYOR_RUNALL_BCK:
		conveyorMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);
		conveyorMotor->Set(-1.0);
		intakeLeftMotor->Set(-1.0);
		intakeRightMotor->Set(1.0);
		break;

	case COMMAND_CONVEYOR_RUNALL_STOP:
		conveyorMotor->Set(0.0);
		intakeLeftMotor->Set(0.0);
		intakeRightMotor->Set(0.0);
		break;

	case COMMAND_SYSTEM_MSGTIMEOUT:
	default:
		break;
	}
}

