#include "AddBeltAction.h"

AddBeltAction::AddBeltAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
void AddBeltAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	///TODO: Make the needed validations on the read parameters

	while (!startPos.IsValidCell() || !endPos.IsValidCell() || (startPos.GetCellNum() == endPos.GetCellNum()))
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell! Click to continue ...");
		pIn->GetCellClicked();
		pOut->PrintMessage("New Belt: Click on its Start Cell ...");
		startPos = pIn->GetCellClicked();
		pOut->PrintMessage("New Belt: Click on its End Cell ...");
		endPos = pIn->GetCellClicked();
	}

	// Clear messages
	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellPosition pos(i, j);
			Belt* nextBelt = pGrid->GetNextBelt(pos);
			if (nextBelt) {
				CellPosition nextBeltStartPos = nextBelt->GetPosition();
				CellPosition nextBeltEndPos = nextBelt->GetEndPosition();
				//check for overlapping with startPos and endPos + check if the start of one belt is the end of another
				if (
					(startPos.GetCellNum() == nextBeltEndPos.GetCellNum()) ||
					(endPos.GetCellNum() == nextBeltStartPos.GetCellNum())
					) {
					pGrid->PrintErrorMessage("Error: Overlapping belts! Click to continue ...");
					return;
				}
				int nextBeltStartPosH = nextBeltStartPos.HCell();
				int nextBeltStartPosV = nextBeltStartPos.VCell();
				int nextBeltEndPosH = nextBeltEndPos.HCell();
				int nextBeltEndPosV = nextBeltEndPos.VCell();
				int startPosH = startPos.HCell();
				int startPosV = startPos.VCell();
				int endPosH = endPos.HCell();
				int endPosV = endPos.VCell();

				//check if the next belt is horizontal
				if (nextBeltStartPosH == nextBeltEndPosH) {
					//check if the new belt is horizontal
					if (startPosH == endPosH) {
						//check if the new belt is in the same row as the next belt
						if (startPosV == nextBeltStartPosV) {
							//check if the new belt is overlapping with the next belt
							if ((startPosH <= nextBeltEndPosH && startPosH >= nextBeltStartPosH) || (endPosH <= nextBeltEndPosH && endPosH >= nextBeltStartPosH)) {
								pGrid->PrintErrorMessage("Error: Overlapping belts! Click to continue ...");
								return;
							}
						}
					}
					else {
						int minH = min(startPosH, endPosH);
						int maxH = max(startPosH, endPosH);
						if (minH <= nextBeltStartPosH && maxH >= nextBeltStartPosH) {
							if ((startPosV <= nextBeltEndPosV && startPosV >= nextBeltStartPosV) || (endPosV <= nextBeltEndPosV && endPosV >= nextBeltStartPosV)) {
								pGrid->PrintErrorMessage("Error: Overlapping belts! Click to continue ...");
								return;
							}
						}
					}
				}
				else {
					//check if the new belt is vertical
					if (startPosV == endPosV) {
						//check if the new belt is in the same column as the next belt
						if (startPosH == nextBeltStartPosH) {
							//check if the new belt is overlapping with the next belt
							if ((startPosV <= nextBeltEndPosV && startPosV >= nextBeltStartPosV) || (endPosV <= nextBeltEndPosV && endPosV >= nextBeltStartPosV)) {
								pGrid->PrintErrorMessage("Error: Overlapping belts! Click to continue ...");
								return;
							}
						}
					}
					else {
						int minV = min(startPosV, endPosV);
						int maxV = max(startPosV, endPosV);
						if (minV <= nextBeltStartPosV && maxV >= nextBeltStartPosV) {
							//check if the new belt is overlapping with the next belt
							if ((startPosH <= nextBeltEndPosH && startPosH >= nextBeltStartPosH) || (endPosH <= nextBeltEndPosH && endPosH >= nextBeltStartPosH)) {
								pGrid->PrintErrorMessage("Error: Overlapping belts! Click to continue ...");
								return;
							}
						}
					}
				}
			}
		}
	}

	// Create a belt object with the parameters read from the user
	Belt * pBelt = new Belt(startPos, endPos);
							
	bool added = pGrid->AddObjectToCell(pBelt);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction

}
AddBeltAction::~AddBeltAction()
{
}
