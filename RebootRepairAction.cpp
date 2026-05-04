#include "RebootRepairAction.h"
#include "ApplicationManager.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"

RebootRepairAction::RebootRepairAction(ApplicationManager *pApp)
    : Action(pApp) {}

void RebootRepairAction::ReadActionParameters() {
  // No parameters needed
}

void RebootRepairAction::Execute() {
  Grid *pGrid = pManager->GetGrid();
  GameState *pState = pManager->GetGameState();

  // Don't act if the game is already over
  if (pState->GetEndGame())
    return;

  Player *pPlayer = pState->GetCurrentPlayer();
  if (!pPlayer)
    return;

  // Step 1: Inform the player
  pGrid->PrintErrorMessage(
      "Rebooting & Repairing... Your health is restored. You will skip movement this round. Click to continue ...");

  // Step 2: Restore health points (add 1 HP)
  int currentHealth = pPlayer->GetHealth();
  if (currentHealth < 10) {
    pPlayer->SetHealth(currentHealth + 1);
  }

  // Step 3: Prevent moving this round
  pPlayer->ClearSavedCommands();
  pPlayer->SetRebooting(true);

  // Step 4: Refresh the UI
  pGrid->UpdateInterface(pState);
}

RebootRepairAction::~RebootRepairAction() {}
