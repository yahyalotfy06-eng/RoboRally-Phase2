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
		// Toolkit repairs the robot by 1 HP (same as visiting a Workshop for repair)
		int newHp = pPlayer->GetHealth() + 1;
		pPlayer->SetHealth(newHp); // SetHealth already clamps to max 10
		pPlayer->SetToolkit(false);
		pGrid->PrintErrorMessage("Toolkit used! Player repaired +1 HP. Click to continue...");
		pGrid->UpdateInterface(pState);
	} else {
		pGrid->PrintErrorMessage("You don't own a Toolkit! Click to continue...");
	}
}
