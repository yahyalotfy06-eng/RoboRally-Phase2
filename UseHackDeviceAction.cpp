#include "UseHackDeviceAction.h"
#include "ApplicationManager.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"

UseHackDeviceAction::UseHackDeviceAction(ApplicationManager *pApp) : Action(pApp) {}
UseHackDeviceAction::~UseHackDeviceAction() {}

void UseHackDeviceAction::ReadActionParameters() {
	// No parameters to read
}

void UseHackDeviceAction::Execute() {
	Grid *pGrid = pManager->GetGrid();
	GameState *pState = pManager->GetGameState();
	Player *pPlayer = pState->GetCurrentPlayer();

	if (!pPlayer) return;

	if (pPlayer->HasHackDevice()) {
		int opponentNum = (pPlayer->GetPlayerNum() + 1) % 2; // Assuming MaxPlayerCount = 2
		Player *pOpponent = pState->GetPlayer(opponentNum);

		if (pOpponent) {
			pOpponent->SetHacked(true);
			pPlayer->SetHackDevice(false);
			pGrid->PrintErrorMessage("Opponent hacked! They will skip their turn. Click to continue...");
		}
	} else {
		pGrid->PrintErrorMessage("You don't own a Hack Device! Click to continue...");
	}
}
