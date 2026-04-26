#pragma once
#include "Action.h"

class ExecuteCommandAction : public Action
{
public:
	ExecuteCommandAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ExecuteCommandAction();
};
