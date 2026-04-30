#include "AddRotatingGearAction.h"
#include "ApplicationManager.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp) : Action(pApp)
{
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	// 2- Read the gearPos
	pOut->PrintMessage("Click on cell to place the rotating gear...");
	gearPos = pIn->GetCellClicked();

	// 3- Read whether the direction will be clockwise or not
	pOut->PrintMessage("Enter direction (1 for clockwise, 0 for anti-clockwise):");
	clockwise = pIn->GetInteger(pOut) == 1;

	// 4- Make the needed validations on the read parameters
	if (!gearPos.IsValidCell() || !pGrid->IsCellEmpty(gearPos))
	{
		pOut->PrintMessage("Invalid position for rotating gear!");
		return;
	}
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	RotatingGear* pGear = new RotatingGear(gearPos, clockwise);
	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!gearPos.IsValidCell() || !pGrid->IsCellEmpty(gearPos))
	{
		pOut->PrintMessage("Error: Cannot place rotating gear here!");
		return;
	}
	// 3-Add the rotating object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pGear);
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
	if (!added)
	{
		pOut->PrintMessage("Error: Cell is already occupied!");
		delete pGear; // prevent memory leak
	}
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
