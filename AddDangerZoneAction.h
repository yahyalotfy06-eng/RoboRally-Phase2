#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "DangerZone.h"
#include "Grid.h"
class AddDangerZoneAction : public Action
{
	CellPosition DangerZonePos;
public:
	AddDangerZoneAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddDangerZoneAction();
};
