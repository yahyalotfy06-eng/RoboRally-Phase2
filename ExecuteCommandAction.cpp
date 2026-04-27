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

  for (int i = 0; i < MaxPlayerCount; i++) {
    Player *pPlayer = pGameState->GetPlayer(i);
    if (pPlayer) {
      pPlayer->Move(pGrid, pGameState);

      pPlayer->ClearSavedCommands();

      if (pGameState->GetEndGame())
        break;
    }
  }

  pGameState->AdvanceCurrentPlayer();
}

ExecuteCommandAction::~ExecuteCommandAction() {}
