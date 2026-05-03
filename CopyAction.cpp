#include "CopyAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

CopyAction::CopyAction(ApplicationManager *pApp) : Action(pApp) {}
CopyAction::~CopyAction() {}

void CopyAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on a game object to copy.");
	copyPos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void CopyAction::Execute() {
	ReadActionParameters();

	if (!copyPos.IsValidCell()) {
		pManager->GetGrid()->PrintErrorMessage("Invalid cell clicked! Click to continue...");
		return;
	}

	Grid* pGrid = pManager->GetGrid();
	Cell* pCell = pGrid->GetCell(copyPos);
	GameObject* pObj = pCell->GetGameObject();

	if (pObj) {
		GameObject* clone = pObj->Clone();
		pGrid->SetClipboard(clone);
		pGrid->PrintErrorMessage("Object copied! Click to continue...");
	} else {
		pGrid->PrintErrorMessage("No object in the selected cell to copy! Click to continue...");
	}
}
