#include "ExecuteCommandAction.h"

#include "Grid.h"
#include "GameState.h"
#include "Player.h"

ExecuteCommandAction::ExecuteCommandAction(ApplicationManager* pApp) : Action(pApp)
{
}

void ExecuteCommandAction::ReadActionParameters()
{
	// No parameters needed for executing commands
}

void ExecuteCommandAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pGameState = pManager->GetGameState();

	// Check if the game has ended before executing
	if (pGameState->GetEndGame())
		return;

	// Loop through all players and execute their saved commands
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* pPlayer = pGameState->GetPlayer(i);
		if (pPlayer)
		{
			// The Move function iterates through the player's saved commands
			pPlayer->Move(pGrid, pGameState);
			
			// Clear the commands after they are executed to prepare for the next round
			pPlayer->ClearSavedCommands();
		}
	}
}

ExecuteCommandAction::~ExecuteCommandAction()
{
}
