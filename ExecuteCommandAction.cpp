#include "ExecuteCommandAction.h"

#include "GameState.h"
#include "Grid.h"
#include "Player.h"

ExecuteCommandAction::ExecuteCommandAction(ApplicationManager *pApp)
    : Action(pApp) {}

void ExecuteCommandAction::ReadActionParameters() {
  // mfesh parameters-----yahya
}

void ExecuteCommandAction::Execute() {
  Grid *pGrid = pManager->GetGrid();
  GameState *pGameState = pManager->GetGameState();

  // Check the game didn't end-----yahya
  if (pGameState->GetEndGame())
    return;

  // Execute only the current player's saved commands, then pass the turn
  Player *pPlayer = pGameState->GetCurrentPlayer();
  if (pPlayer) {
    pPlayer->Move(pGrid, pGameState);
    pPlayer->ClearSavedCommands();
  }

  if (!pGameState->GetEndGame()) {
    pGameState->AdvanceCurrentPlayer();
    pGameState->GenerateAvailableCommands();
    pGrid->UpdateInterface(pGameState);
  }
}

ExecuteCommandAction::~ExecuteCommandAction() {}
