#pragma once
#include "Action.h"
#include <fstream>
#include <string>
#include "DEFS.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "WaterPit.h"
#include"DangerZone.h"
#include"GameObject.h"
#include "Flag.h"
#include"Belt.h"
#include "Workshop.h"
#include "Antenna.h"
#include"RotatingGear.h"

class LoadGridAction : public Action
{
	std::string fileName;
	GameObjectType ArrOrderTypes[7];
	GameObject* CreateObject(GameObjectType type);

public:
	LoadGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~LoadGridAction();
};

