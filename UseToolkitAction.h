#pragma once

#include "Action.h"

class UseToolkitAction : public Action {
public:
	UseToolkitAction(ApplicationManager *pApp);
	virtual ~UseToolkitAction();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
};
