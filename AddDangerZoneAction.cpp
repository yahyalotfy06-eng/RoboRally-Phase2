#include "AddDangerZoneAction.h"
AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddDangerZoneAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();

    pOut->PrintMessage("Click on a cell to place the Danger Zone.");
    DangerZonePos = pIn->GetCellClicked();


    if (!(DangerZonePos.IsValidCell()) || !(pGrid->IsCellEmpty(DangerZonePos)))
    {
        pOut->PrintMessage("Invalid cell selected! The Action is canceled. Click to continue");
        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        DangerZonePos = CellPosition(-1, -1);
        return;
    }
    pOut->ClearStatusBar();
}

void AddDangerZoneAction::Execute()
{
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
    if (!(DangerZonePos.IsValidCell()))
        return;
    DangerZone* pDangerZone = new DangerZone(DangerZonePos);
    bool empty = pGrid->AddObjectToCell(pDangerZone);
    if (!empty)
    {
        pGrid->PrintErrorMessage("Cannot add Danger Zone, Cell is invalid or occupied, Click to continue.");
        delete pDangerZone;
        return;
    }
}

AddDangerZoneAction::~AddDangerZoneAction()
{
}

