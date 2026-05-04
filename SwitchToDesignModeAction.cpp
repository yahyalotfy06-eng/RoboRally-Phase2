
#include "SwitchToDesignModeAction.h"
#include "GameState.h"
#include "Grid.h"
#include "Output.h"


SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager *pApp)
    : Action(pApp) {}

void SwitchToDesignModeAction::ReadActionParameters() {
  // No parameters needed -- a mode switch requires no user input
}

void SwitchToDesignModeAction::Execute() {
  Grid *pGrid = pManager->GetGrid();
  Output *pOut = pGrid->GetOutput();

  // 1. Switch the global interface mode to Design Mode
  UI.InterfaceMode = MODE_DESIGN;

  // 2. Redraw the toolbar with Design Mode buttons
  pOut->CreateDesignModeToolBar(); // updates toolbar

  // 3. Cleanup when leaving Play Mode
  pOut->ClearStatusBar();
  pOut->ClearCommandsBar();
  pManager->GetGameState()->ResetGame(pGrid);

  // 4. Update the full interface so the grid is redrawn
  pManager->UpdateInterface();
}

SwitchToDesignModeAction::~SwitchToDesignModeAction() {}
