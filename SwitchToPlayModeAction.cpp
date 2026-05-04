#include "SwitchToPlayModeAction.h"
#include "GameState.h"
#include "Grid.h"
#include "Output.h"
#include "Antenna.h"
#include <cstdlib>
#include <ctime>

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager *pApp)
    : Action(pApp) {}

void SwitchToPlayModeAction::ReadActionParameters() {
  // No parameters needed -- a mode switch requires no user input
}

void SwitchToPlayModeAction::Execute() {
  Output *pOut = pManager->GetGrid()->GetOutput();
  GameState *pState = pManager->GetGameState();
  Grid *pGrid = pManager->GetGrid();

  // 1. Switch the global interface mode to Play Mode
  UI.InterfaceMode = MODE_PLAY;

  // 2. Redraw the toolbar with Play Mode buttons
  pOut->CreatePlayModeToolBar();

  // 3. Reset game state for the new play session ----shahd
  pState->ResetGame(pGrid);
  // the todo is to reset the game

  // === Initial Turn Order Calculation ===
  Antenna *pAntenna = pGrid->GetAntenna();
  if (pAntenna) {
    pAntenna->Apply(pGrid, pState, pState->GetCurrentPlayer());
  }

  // === Generate Random Commands in the Commands Bar ===
  srand((unsigned int)time(NULL));
  pState->GenerateAvailableCommands();

  // 4. Redraw the full interface (board + player info bar + commands bar)
  pManager->UpdateInterface();
}

SwitchToPlayModeAction::~SwitchToPlayModeAction() {}
