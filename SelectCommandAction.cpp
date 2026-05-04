#include "SelectCommandAction.h"
#include "ApplicationManager.h"
#include "GameState.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"

SelectCommandAction::SelectCommandAction(ApplicationManager *pApp)
    : Action(pApp) {}

SelectCommandAction::~SelectCommandAction() {}

void SelectCommandAction::ReadActionParameters() {
  // mfesh parameters
}

void SelectCommandAction::Execute() {
  Grid *pGrid = pManager->GetGrid();
  Output *pOut = pGrid->GetOutput();
  Input *pIn = pGrid->GetInput();
  GameState *pState = pManager->GetGameState();
  Player *pPlayer = pState->GetCurrentPlayer();

  if (!pPlayer) {
    return;
  }

  if (pPlayer->IsRebooting()) {
    pOut->PrintMessage("You are rebooting this round and cannot select commands!");
    return;
  }

  int maxCommands = pPlayer->HasExtendedMemory() ? 6 : 5;
  if (pPlayer->GetSavedCommandCount() >= maxCommands) {
    pOut->PrintMessage(
        "Max saved commands reached! You must execute them now.");
    return;
  }

  pOut->PrintMessage("Click on an available command to select it.");

  int cmdIndex = pIn->GetSelectedCommandIndex();

  if (cmdIndex != -1) {
    // Look up the actual command at the clicked visual position (respects
    // shuffle order)
    Command cmd = pState->GetAvailableCommand(cmdIndex);

    pPlayer->AddSavedCommand(cmd);

    pOut->PrintMessage("Command selected successfully!");

    pGrid->UpdateInterface(pState);
  }

  else {
    pOut->PrintMessage(
        "Invalid click! Please click exactly on an available command icon.");
  }
}
