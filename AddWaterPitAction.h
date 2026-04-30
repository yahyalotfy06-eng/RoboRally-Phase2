#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "WaterPit.h"
class AddWaterPitAction : public Action
{
	CellPosition WaterPitPos;
public:
	AddWaterPitAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddWaterPitAction();
};
