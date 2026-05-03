#pragma once
#include "Action.h"

class PasteAction : public Action {
	CellPosition pastePos;
public:
	PasteAction(ApplicationManager *pApp);
	virtual ~PasteAction();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
};
