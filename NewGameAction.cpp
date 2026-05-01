#include "NewGameAction.h"
#include "ApplicationManager.h"
#include "Gamestate.h"

NewGameAction::NewGameAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void NewGameAction::ReadActionParameters(){

}

void NewGameAction::Execute()
{
    ReadActionParameters();

    GameState* pGameState = pManager->GetGameState();
    Grid* pGrid = pManager->GetGrid();

    pGameState->ResetGame(pGrid);
}

NewGameAction::~NewGameAction()
{
    // Nothing to clean up
}