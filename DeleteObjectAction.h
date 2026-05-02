#pragma once
#include "Action.h"
class DeleteObjectAction :public Action
{
	private:
	CellPosition pos; //store chosen position (cell)

public:
	DeleteObjectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); //reads the cell that will be deleted
	virtual void Execute();               //deletes the obj
};