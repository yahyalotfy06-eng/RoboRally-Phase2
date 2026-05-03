#include "PasteAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

PasteAction::PasteAction(ApplicationManager *pApp) : Action(pApp) {}
PasteAction::~PasteAction() {}

void PasteAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on a cell to paste the game object.");
	pastePos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void PasteAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	GameObject* pClipboard = pGrid->GetClipboard();

	if (!pClipboard) {
		pGrid->PrintErrorMessage("Clipboard is empty! Copy or cut an object first. Click to continue...");
		return;
	}

	ReadActionParameters();

	if (!pastePos.IsValidCell()) {
		pGrid->PrintErrorMessage("Invalid cell clicked! Click to continue...");
		return;
	}

	// Clone the clipboard object so we can paste multiple times
	GameObject* clone = pClipboard->Clone();
	clone->SetPosition(pastePos); // update its position to the clicked cell

	if (pGrid->AddObjectToCell(clone)) {
		pGrid->UpdateInterface(pManager->GetGameState());
		pGrid->PrintErrorMessage("Object pasted! Click to continue...");
	} else {
		// e.g. if the cell is not empty, or if it's a belt that extends off the grid
		delete clone;
		pGrid->PrintErrorMessage("Cannot paste here (cell occupied or object out of bounds). Click to continue...");
	}
}
