#include "UseToolkitAction.h"
#include "ApplicationManager.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"
#include "Output.h"

UseToolkitAction::UseToolkitAction(ApplicationManager *pApp) : Action(pApp) {}
UseToolkitAction::~UseToolkitAction() {}

void UseToolkitAction::ReadActionParameters() {
	// No parameters to read
}

void UseToolkitAction::Execute() {
	Grid *pGrid = pManager->GetGrid();
	GameState *pState = pManager->GetGameState();
	Player *pPlayer = pState->GetCurrentPlayer();

	if (!pPlayer) return;

	if (pPlayer->HasToolkit()) {
		pPlayer->SetHealth(10); // user requested toolkit should only repair the robot to max
		pPlayer->SetToolkit(false);
		pGrid->PrintErrorMessage("Toolkit used! Player fully repaired. Click to continue...");
		pGrid->UpdateInterface(pState);
	} else {
		pGrid->PrintErrorMessage("You don't own a Toolkit! Click to continue...");
	}
}
