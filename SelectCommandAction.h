#pragma once  //
#include "Action.h"

class SelectCommandAction : public Action
{
public:
	SelectCommandAction(ApplicationManager* pApp);
	virtual ~SelectCommandAction();

	virtual void ReadActionParameters();
	virtual void Execute();
};
