#include "CutAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

CutAction::CutAction(ApplicationManager *pApp) : Action(pApp) {}
CutAction::~CutAction() {}

void CutAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on a game object to cut.");
	cutPos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void CutAction::Execute() {
	ReadActionParameters();

	if (!cutPos.IsValidCell()) {
		pManager->GetGrid()->PrintErrorMessage("Invalid cell clicked! Click to continue...");
		return;
	}

	Grid* pGrid = pManager->GetGrid();
	Cell* pCell = pGrid->GetCell(cutPos);
	GameObject* pObj = pCell->GetGameObject();

	if (pObj) {
		GameObject* clone = pObj->Clone();
		pGrid->SetClipboard(clone);
		pGrid->RemoveObjectFromCell(cutPos); // this deletes the original
		pGrid->UpdateInterface(pManager->GetGameState());
		pGrid->PrintErrorMessage("Object cut! Click to continue...");
	} else {
		pGrid->PrintErrorMessage("No object in the selected cell to cut! Click to continue...");
	}
}
