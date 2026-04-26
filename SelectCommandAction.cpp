#include "SelectCommandAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "GameState.h"
#include "Player.h"
#include "ApplicationManager.h"

SelectCommandAction::SelectCommandAction(ApplicationManager* pApp) : Action(pApp)
{
}



SelectCommandAction::~SelectCommandAction()
{
}



void SelectCommandAction::ReadActionParameters()
{
	// mfesh parameters
}

void SelectCommandAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();

	if (!pPlayer) {
		return;
	}


	if (pPlayer->GetSavedCommandCount() >= MaxSavedCommands)
	{
		pOut->PrintMessage("Max saved commands reached! You must execute them now.");
		return;
	}


	pOut->PrintMessage("Click on an available command to select it.");

	int cmdIndex = pIn->GetSelectedCommandIndex();

	if (cmdIndex != -1)
	{
		Command cmd = (Command)(cmdIndex + 1); 

		pPlayer->AddSavedCommand(cmd);

		pOut->PrintMessage("Command selected successfully!");
		
		pGrid->UpdateInterface(pState);
	}

	else
	{
		pOut->PrintMessage("Invalid click! Please click exactly on an available command icon.");
	}
}
