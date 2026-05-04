#include "ExecuteCommandAction.h"

#include "Antenna.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"
#include <string>

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
      pGrid->PrintErrorMessage(
          "Player " + to_string(pPlayer->GetPlayerNum()) +
          " is hacked and will skip this round! Click to continue...");
      pPlayer->SetHacked(false);
    } else if (pPlayer->IsRebooting()) {
      pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) +
                               " is rebooting and will skip movement this "
                               "round! Click to continue...");
      pPlayer->SetRebooting(false);
    } else {
      pPlayer->Move(pGrid, pGameState);
    }
    pPlayer->ClearSavedCommands();
  }

  if (!pGameState->GetEndGame()) {
    pGameState->AdvanceCurrentPlayer();

    // When the order index resets to 0, a full round has just ended.
    // This is when we run the shooting phase (once per round), then
    // recalculate the antenna turn order for the next round.
    if (pGameState->GetCurrentOrderIndex() == 0) {
      // --- Shooting Phase (fires once per round, after all movement) ---
      pGameState->ExecuteShootingPhase(pGrid);

      if (!pGameState->GetEndGame()) {
        // --- Antenna recalculates turn order for the next round ---
        Antenna *pAntenna = pGrid->GetAntenna();
        if (pAntenna) {
          pAntenna->Apply(pGrid, pGameState, pGameState->GetCurrentPlayer());
        }
      }
    }

    if (!pGameState->GetEndGame()) {
      pGameState->GenerateAvailableCommands();
      pGrid->UpdateInterface(pGameState);
    }
  }
}

ExecuteCommandAction::~ExecuteCommandAction() {}
