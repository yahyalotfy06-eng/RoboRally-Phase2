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
    if (pPlayer->IsHacked()) {
      pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " is hacked and will skip this round! Click to continue...");
      pPlayer->SetHacked(false);
    } else {
      pPlayer->Move(pGrid, pGameState);
    }
    pPlayer->ClearSavedCommands();
  }

  // Trigger Shooting Phase after movement
  if (!pGameState->GetEndGame()) {
    pGameState->ExecuteShootingPhase(pGrid);
  }

  if (!pGameState->GetEndGame()) {
    pGameState->AdvanceCurrentPlayer();
    pGameState->GenerateAvailableCommands();
    pGrid->UpdateInterface(pGameState);
  }
}

ExecuteCommandAction::~ExecuteCommandAction() {}
