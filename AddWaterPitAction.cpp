#include "AddWaterPitAction.h"

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{

}

void AddWaterPitAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();

    pOut->PrintMessage("Click on a cell to place the Water Pit.");
    WaterPitPos = pIn->GetCellClicked();


    if (!(WaterPitPos.IsValidCell()) || !(pGrid->IsCellEmpty(WaterPitPos)))
    {
        pOut->PrintMessage("Invalid cell selected, The Action is canceled. Click to continue");
        int x, y;
        pIn->GetPointClicked(x, y);
        WaterPitPos = CellPosition(-1, -1);
        return;
    }


    pOut->ClearStatusBar();
}

void AddWaterPitAction::Execute()
{
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
    if (!(WaterPitPos.IsValidCell()))
        return;
    WaterPit* pWaterPit = new WaterPit(WaterPitPos);
    bool empty = pGrid->AddObjectToCell(pWaterPit);
    if (!empty)
    {
        pGrid->PrintErrorMessage("Cannot add WaterPit, Cell is invalid or occupied, Click to continue.");
        delete pWaterPit;
        return;
    }
}

AddWaterPitAction::~AddWaterPitAction()
{
}

