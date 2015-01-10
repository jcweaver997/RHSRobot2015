#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>

#include <WPILib.h>

//Robot
#include "ComponentBase.h"
#include "RobotParams.h"

//Local
#include "Autonomous.h"
#include "AutoParser.h"

using namespace std;

// these must match the enumeration above!!

const char *szTokens[] = 
{
		"MODE",
		"BEGIN",
		"DELAY",
		"END",
		"NOP"
};

void Autonomous::Evaluate(std::string rStatement)
{
	char *pToken;
	char *pCurrLinePos;
	int iCommand;
	float fParam1;

	string rStatus;

	if(rStatement.empty())
	{
		return;
	}

	// process the autonomous motion

	pCurrLinePos = (char *)rStatement.c_str();
	printf("%s\n", rStatement.c_str());

	if(*pCurrLinePos == sComment)
	{
		rStatus.append("comment");
		printf("%s\n", rStatus.c_str());
		return;
	}

	// find first token

	pToken = strtok_r(pCurrLinePos, szDelimiters, &pCurrLinePos);

	// which command are we to execute??
	// this can be (easily) be made much faster... any student want to improve on this?

	for(iCommand = AUTO_TOKEN_MODE; iCommand < AUTO_TOKEN_LAST; iCommand++)
	{
		if(!strncmp(pToken, 
				szTokens[iCommand], 
				strlen(szTokens[iCommand])))
		{
			break;
		}
	}

	if(iCommand == AUTO_TOKEN_LAST)
	{
		// no valid token found
		rStatus.append("no tokens");
		printf("%s\n", rStatus.c_str());
		return;
	}

	// execute the proper command

	switch (iCommand)
	{
	case AUTO_TOKEN_BEGIN:
		rStatus.append("start");
		break;

	case AUTO_TOKEN_END:
		rStatus.append("done");
		break;

	case AUTO_TOKEN_DELAY:
		pToken = strtok_r(pCurrLinePos, szDelimiters, &pCurrLinePos);

		if(pToken == NULL)
		{
			rStatus.append("missing parameter");
		}
		else
		{
			fParam1 = atof(pToken);
			rStatus.append("wait");
			Wait(fParam1);
		}
		break;	

	default:
		rStatus.append("unknown token");
		break;;
	}

	printf("%s\n", rStatus.c_str());
}

