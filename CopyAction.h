#pragma once
#include "Action.h"

class CopyAction : public Action {
	CellPosition copyPos;
public:
	CopyAction(ApplicationManager *pApp);
	virtual ~CopyAction();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
};
