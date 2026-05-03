#include "AddFlagAction.h"

AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp) {
  // Initializes the pManager pointer of Action with the passed pointer
}

void AddFlagAction::ReadActionParameters() {
  /// TODO: Implement this function as mentioned in the guideline steps
  /// (numbered below) below

  // == Here are some guideline steps (numbered below) to implement this
  // function ==

  // 1- Get a Pointer to the Input / Output Interfaces
  Grid *pGrid = pManager->GetGrid();
  Output *pOut = pGrid->GetOutput();
  Input *pIn = pGrid->GetInput();

  // 2- Read the flagPos
  pOut->PrintMessage("New Flag: Click on its Cell ...");
  flagPos = pIn->GetCellClicked();

  // 4- Make the needed validations on the read parameters
  while (!flagPos.IsValidCell() || flagPos.GetCellNum() == 1) {
    pGrid->PrintErrorMessage("Error: Invalid Cell! Click to continue ...");
    pOut->PrintMessage("New Flag: Click on its Cell ...");
    flagPos = pIn->GetCellClicked();
  }

  // 5- Clear status bar
  pOut->ClearStatusBar();
}
void AddFlagAction::resetisflag() { AddFlagAction::isFlagAdded = false; }
void AddFlagAction::Execute() {
  // The first line of any Action Execution is to read its parameter first
  // and hence initializes its data members
  ReadActionParameters();
  /// TODO: Implement this function as mentioned in the guideline steps
  /// (numbered below) below
  // == Here are some guideline steps (numbered below) to implement this
  // function ==

  // 1-Create a flag object
  Flag *pFlag = new Flag(flagPos);
  // 2-get a pointer to the Grid from the ApplicationManager
  Grid *pGrid = pManager->GetGrid();
  if (AddFlagAction::isFlagAdded) {
    pGrid->PrintErrorMessage(
        "Error: You can't add more than one flag ! Click to continue ...");
    return;
  }
  // 3-Add the flag object to the GameObject of its Cell:
  bool added = pGrid->AddObjectToCell(pFlag);
  // 4-Check if the flag was added and print an errror message if flag couldn't
  // be added
  if (!added) {
    pGrid->PrintErrorMessage(
        "Error: Cell already has an object ! Click to continue ...");
  } else {
    AddFlagAction::isFlagAdded = true;
  }
}

AddFlagAction::~AddFlagAction() {}
bool AddFlagAction::isFlagAdded = false;