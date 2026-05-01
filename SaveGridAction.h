#pragma once
#include "Action.h"
#include <fstream>
#include "DEFS.h"
#include "Action.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"

class SaveGridAction :public Action
{
	string fileName;
	GameObjectType ArrOrderTypes[7] = {
		FLAG_TYPE,
		WATERPIT_TYPE,
		DANGERZONE_TYPE,
		BELT_TYPE,
		WORKSHOP_TYPE,
		ANTENNA_TYPE,
		ROTATINGGEAR_TYPE,
	};

public:
	SaveGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SaveGridAction();
};