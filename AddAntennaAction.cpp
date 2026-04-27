#include "AddAntennaAction.h"
AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddAntennaAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Antenna: Click on its Cell ...");
	antennaPosition = pIn->GetCellClicked();

	while (!antennaPosition.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell! Click to continue ...");
		pOut->PrintMessage("New Antenna: Click on its Cell ...");
		antennaPosition = pIn->GetCellClicked();
	}
	pOut->ClearStatusBar();
}

void AddAntennaAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); 

	if (AddAntennaAction::isAntennaAdded)
	{
		pGrid->PrintErrorMessage("Error: You can't add more than one antenna ! Click to continue ...");
		return;
	}

	Antenna* pAntenna = new Antenna(antennaPosition);


	bool added = pGrid->AddObjectToCell(pAntenna);

	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	else
	{
		AddAntennaAction::isAntennaAdded = true;
	}
}

void AddAntennaAction::resetisantenna()
{
	AddAntennaAction::isAntennaAdded = false;
}

AddAntennaAction::~AddAntennaAction()
{
}

bool AddAntennaAction::isAntennaAdded = false; 