#pragma once
#include "Action.h"
#include <fstream>
#include "DEFS.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Waterpit.h"
#include"DangerZone.h"
#include"GameObject.h"
#include "Flag.h"
#include"Belt.h"
#include "Workshop.h"
#include "Antenna.h"
#include"RotatingGear.h"

class LoadGridAction : public Action
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
	GameObject* CreateObject(GameObjectType type);

public:
	LoadGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~LoadGridAction();
};

