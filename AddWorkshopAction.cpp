#include "AddWorkshopAction.h"
AddWorkShopAction::AddWorkShopAction(ApplicationManager *pApp) : Action(pApp) {}

void AddWorkShopAction::ReadActionParameters() {
  Grid *pGrid = pManager->GetGrid();
  Input *pIn = pGrid->GetInput();
  Output *pOut = pGrid->GetOutput();

  pOut->PrintMessage("Click on a cell to place the WorkShop.");
  WorkShopPos = pIn->GetCellClicked();

  if (!(WorkShopPos.IsValidCell()) || !(pGrid->IsCellEmpty(WorkShopPos))) {
    pOut->PrintMessage(
        "Invalid cell selected! The Action is canceled. Click to continue");
    int x, y;
    pIn->GetPointClicked(x, y);
    WorkShopPos = CellPosition(-1, -1);
    return;
  }
  pOut->ClearStatusBar();
}

void AddWorkShopAction::Execute() {
  ReadActionParameters();
  Grid *pGrid = pManager->GetGrid();
  if (!(WorkShopPos.IsValidCell()))
    return;
  Workshop *pWorkshop = new Workshop(WorkShopPos);
  bool empty = pGrid->AddObjectToCell(pWorkshop);
  if (!empty) {
    pGrid->PrintErrorMessage(
        "Cannot add Workshop, Cell is invalid or occupied, Click to continue.");
    delete pWorkshop;
    return;
  }
}

AddWorkShopAction::~AddWorkShopAction() {}
