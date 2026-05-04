#include "NewGameAction.h"
#include "ApplicationManager.h"
#include "Gamestate.h"
#include "Grid.h"
#include "Antenna.h"
#include <cstdlib>
#include <ctime>

NewGameAction::NewGameAction(ApplicationManager *pApp) : Action(pApp) {}

void NewGameAction::ReadActionParameters() {}

void NewGameAction::Execute() {
  ReadActionParameters();

  GameState *pGameState = pManager->GetGameState();
  Grid *pGrid = pManager->GetGrid();

  pGrid->ClearGrid(); // Clear all game objects from the board in memory
  pGrid->GetOutput()->ClearGridArea(); // Visually erase the board

  pGameState->ResetGame(pGrid); // This redraws the players at the start position

  // Re-render the Play Mode toolbar (icons may need refreshing)
  pGrid->GetOutput()->CreatePlayModeToolBar();

  // Recalculate antenna turn order for the fresh game
  Antenna *pAntenna = pGrid->GetAntenna();
  if (pAntenna) {
    pAntenna->Apply(pGrid, pGameState, pGameState->GetCurrentPlayer());
  }

  // === Generate Random Commands for the New Game ===
  srand((unsigned int)time(NULL));
  pGameState->GenerateAvailableCommands();

  // === Update the interface to show the new commands and reset board ===
  pGrid->UpdateInterface(pGameState);
}

NewGameAction::~NewGameAction() {
  // Nothing to clean up
}