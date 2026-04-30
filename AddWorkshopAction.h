#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "WorkShop.h"
class AddWorkShopAction : public Action
{
	CellPosition WorkShopPos;
public:
	AddWorkShopAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddWorkShopAction();
};

