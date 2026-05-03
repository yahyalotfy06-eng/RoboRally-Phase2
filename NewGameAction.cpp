#include "NewGameAction.h"
#include "ApplicationManager.h"
#include "Gamestate.h"
#include "Grid.h"

NewGameAction::NewGameAction(ApplicationManager *pApp) : Action(pApp) {}

void NewGameAction::ReadActionParameters() {}

void NewGameAction::Execute() {
  ReadActionParameters();

  GameState *pGameState = pManager->GetGameState();
  Grid *pGrid = pManager->GetGrid();

  pGameState->ResetGame(pGrid);
  
  // === Generate Random Commands for the New Game ===
  srand((unsigned int)time(NULL));
  pGameState->GenerateAvailableCommands();
  
  // === Update the interface to show the new commands and reset board ===
  pGrid->UpdateInterface(pGameState);
}

NewGameAction::~NewGameAction() {
  // Nothing to clean up
}