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
      "Rebooting player... You lose 1 HP. Click to continue ...");

  // Step 2: Reduce health by 1
  int newHealth = pPlayer->GetHealth() - 1;
  pPlayer->SetHealth(newHealth);

  // Step 3: If health reached zero, the player is dead — game over
  if (pPlayer->GetHealth() == 0) {
    pGrid->PrintErrorMessage("Player has no health left after reboot! Game "
                             "over. Click to continue ...");
    pState->SetEndGame(true);
    pGrid->UpdateInterface(pState);
    return;
  }

  // Step 4: Move the player back to the start cell
  pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());

  // Step 5: Reset direction to RIGHT
  pPlayer->SetDirection(RIGHT);

  // Step 6: Clear any saved commands (the "repair" part)
  pPlayer->ClearSavedCommands();

  // Step 7: Refresh the UI
  pGrid->UpdateInterface(pState);

  pGrid->PrintErrorMessage(
      "Reboot complete! Player returned to start. Click to continue ...");
}

RebootRepairAction::~RebootRepairAction() {}
