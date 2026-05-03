#pragma once

#include "Action.h"

class UseHackDeviceAction : public Action {
public:
	UseHackDeviceAction(ApplicationManager *pApp);
	virtual ~UseHackDeviceAction();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
};
