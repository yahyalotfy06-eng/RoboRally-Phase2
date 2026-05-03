#pragma once
#include "Action.h"

class CutAction : public Action {
	CellPosition cutPos;
public:
	CutAction(ApplicationManager *pApp);
	virtual ~CutAction();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
};
