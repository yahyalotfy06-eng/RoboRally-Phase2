#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Antenna.h"
#include "Grid.h"
class AddAntennaAction :
	public Action
{

	CellPosition antennaPosition;

	static bool isAntennaAdded; 
public:
	AddAntennaAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	static void resetisantenna();

	virtual ~AddAntennaAction();
};


