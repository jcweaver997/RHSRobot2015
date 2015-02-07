/*
 * The Clicker component class handles both the Cube's tote lifting
 * and the intake roller.
 */

#include "WPILib.h"

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Clicker.h"
#include <time.h>

Clicker::Clicker()
: ComponentBase(CLICKER_TASKNAME, CLICKER_QUEUE, CLICKER_PRIORITY)
{
	bEnableAutoCycle = false;

	// run the clicker motor in braking mode till it hits a limit switch

	clickerMotor = new CANTalon(CAN_CUBE_CLICKER);
	wpi_assert(clickerMotor);
	clickerMotor->SetVoltageRampRate(120.0);
	clickerMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	clickerMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	// run the intake motor unless a tote has broken the beam

	intakeMotor = new CANTalon(CAN_CUBE_INTAKE);
	intakeMotor->ConfigLimitMode(CANSpeedController::kLimitMode_SwitchInputsOnly);

	pTask = new Task(CLICKER_TASKNAME, (FUNCPTR) &Clicker::StartTask,
			CLICKER_PRIORITY, CLICKER_STACKSIZE);
	wpi_assert(pTask);
	pTask->Start((int)this);
};

Clicker::~Clicker()
{
	delete(pTask);
};

void Clicker::OnStateChange()
{
	switch (localMessage.command)
	{
		case COMMAND_ROBOT_STATE_AUTONOMOUS:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_TEST:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_TELEOPERATED:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_DISABLED:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		case COMMAND_ROBOT_STATE_UNKNOWN:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;

		default:
			clickerMotor->Set(0.0);
			intakeMotor->Set(0.0);
			bEnableAutoCycle = false;
			break;
	}
};

void Clicker::Run()
{

	 // temp variables until we figure it out with the talons
	bool irsens = true;
	bool hallEffectTop = true;
	bool hallEffectBottom = true;

	if(time(NULL)*1000 > (LastChecked+(1.0/CUBECLICKER_SAFETY_CHECKS*1000))){
		LastChecked = time(NULL)*1000;
		if(clickerMotor->GetOutputCurrent() > CUBECLICKER_MAX_AMPS){
				switch(LastState){
				case STATE_CUBECLICKER_RAISE:
					LastState = STATE_CUBECLICKER_TOP;
					Top();
					break;
				case STATE_CUBECLICKER_LOWER:
					LastState = STATE_CUBECLICKER_BOTTOM;
					Bottom();
					break;
				default:
					Bottom();
					break;
				}
				return;
			}
	}


	if(localMessage.command == COMMAND_CUBEAUTOCYCLE_START){
		bEnableAutoCycle = true;
		LastState = STATE_CUBECLICKER_TOP;
	}
	if(localMessage.command == COMMAND_CUBEAUTOCYCLE_STOP){
		bEnableAutoCycle = false;
	}

	if(bEnableAutoCycle)
	switch(LastState){
	case STATE_CUBECLICKER_RAISE:
		if(!hallEffectTop){
			LastState = STATE_CUBECLICKER_RAISE;
			Raise();
		}else{
			LastState = STATE_CUBECLICKER_TOP;
			Top();
		}
		break;
	case STATE_CUBECLICKER_LOWER:
		if(!hallEffectBottom){
			LastState = STATE_CUBECLICKER_LOWER;
			Lower();
		}else{
			LastState = STATE_CUBECLICKER_BOTTOM;
			Bottom();
		}
	break;
	case STATE_CUBECLICKER_TOP:
		if(irsens){
			LastState = STATE_CUBECLICKER_LOWER;
			Lower();
		}else{
			LastState = STATE_CUBECLICKER_TOP;
			Top();
		}
	break;
	case STATE_CUBECLICKER_BOTTOM:
		if(NumOfTotes == CUBECLICKER_MAX_TOTES){
			if(irsens){
				LastState = STATE_CUBECLICKER_TOP;
				Top();
			}else{
				NumOfTotes = 1;
				LastState = STATE_CUBECLICKER_RAISE;
				Raise();
			}
		}else{
			NumOfTotes++;
			LastState = STATE_CUBECLICKER_RAISE;
			Raise();
		}
	break;

	}
	else{ // non auto cycle

		switch (localMessage.command){
		case COMMAND_CUBECLICKER_RAISE:

			hitBottom = false;
			if(!hitTop){
				if(hallEffectTop){
					hitTop = true;
					clickerMotor->Set(0);
				}else{
					clickerMotor->Set(1);
				}
			}else{
				clickerMotor->Set(0);
			}

			break;
		case COMMAND_CUBECLICKER_LOWER:

			hitTop = false;
			if(!hitBottom){
				if(hallEffectBottom){
					hitBottom = true;
					clickerMotor->Set(0);
				}else{
					clickerMotor->Set(-1);
				}
			}else{
				clickerMotor->Set(0);
			}

			break;
		case COMMAND_CUBECLICKER_STOP:
			clickerMotor->Set(0);
			break;
		case COMMAND_CUBEINTAKE_RUN:
			intakeMotor->Set(1);
			break;
		case COMMAND_CUBEINTAKE_STOP:
			intakeMotor->Set(0);
			break;
		default:
			break;
		}

	}


};
void Clicker::Top()
{
	clickerMotor->Set(0);
	intakeMotor->Set(1);
};
void Clicker::Bottom()
{
	clickerMotor->Set(0);
	intakeMotor->Set(0);
};
void Clicker::Raise()
{
	clickerMotor->Set(1);
	intakeMotor->Set(1);
};
void Clicker::Lower()
{
	clickerMotor->Set(-1);
	intakeMotor->Set(0);
};
