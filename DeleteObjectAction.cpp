#include "DeleteObjectAction.h"
#include "Grid.h"
#include"CellPosition.h"
#include"Output.h"
#include "GameObject.h"

DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp) :Action(pApp) { //shahd

}
void DeleteObjectAction::ReadActionParameters() { //getting user input
	Grid* pGrid = pManager->GetGrid(); //get grid
	//get input&output from grid
	Input* pIn = pGrid->GetInput();
	Output* pOut= pGrid->GetOutput();

	pOut->PrintMessage(" Click on the cell to delete its game object");
	//wait for user t click on cell and then store it in pos
	pos = pIn->GetCellClicked(); //pos to store cell user clicked (r,c)
	//clear msg
	pOut->ClearStatusBar();
}

void DeleteObjectAction::Execute() {
	//get the clicked cell
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); //gets grid of the obj that will be deleted
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	int x, y;  //for GetPointClicked to store clicked position on screen
	            //after obj deleted 

	//check the cell
	if (!pos.IsValidCell()) {
		pOut->PrintMessage("Invalid cell! click anywhere to continue... ");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}

	Cell* pCell = pGrid->GetCell(pos); //get selected cel
	//check if cell has obj or not 
	if (!pCell || pCell->GetGameObject() == NULL) {
		pOut->PrintMessage("No Object found! click anywhere to continue... ");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}

	pGrid->RemoveObjectFromCell(pos); //remove obj from grid

	//after obj deleted 
	pManager->UpdateInterface(); //to update the interface 3ltol m3 el "output of successful msg"
	
	pOut->PrintMessage("Game Object has deleted Successfully! Click anywhere to continue...");
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}