#include "SwitchToPlayModeAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"
#include <cstdlib>
#include <ctime>

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// No parameters needed -- a mode switch requires no user input
}

void SwitchToPlayModeAction::Execute()
{
	Output*    pOut   = pManager->GetGrid()->GetOutput();
	GameState* pState = pManager->GetGameState();

	// 1. Switch the global interface mode to Play Mode
	UI.InterfaceMode = MODE_PLAY;

	// 2. Redraw the toolbar with Play Mode buttons
	pOut->CreatePlayModeToolBar();

	// 3. Reset game state for the new play session
	pState->SetCurrentPhase(PHASE_MOVEMENT);

	// 4. Redraw the full interface (board + player info bar)
	pManager->UpdateInterface();

	///TODO: Add any other initialisation needed when entering Play Mode.

	// === Display Random Commands in the Commands Bar ===
	// Build the full list of all real commands (skip NO_COMMAND at index 0)
	Command allCommands[COMMANDS_COUNT - 1];
	for (int i = 0; i < COMMANDS_COUNT - 1; i++)
		allCommands[i] = (Command)(i + 1);

	// Shuffle randomly so the order is different each time
	srand((unsigned int)time(NULL));
	for (int i = COMMANDS_COUNT - 2; i > 0; i--)
	{
		int j = rand() % (i + 1);
		Command temp = allCommands[i];
		allCommands[i] = allCommands[j];
		allCommands[j] = temp;
	}

	// Store the shuffled order in GameState so SelectCommandAction can map clicks correctly
	pState->SetAvailableCommands(allCommands, COMMANDS_COUNT - 1);

	// Show the commands bar with the shuffled available commands and no saved commands yet
	Command emptySaved[MaxSavedCommands] = {};
	pOut->CreateCommandsBar(emptySaved, 0, allCommands, COMMANDS_COUNT - 1);
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
