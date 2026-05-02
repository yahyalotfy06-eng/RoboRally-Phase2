#include "Flag.h"
#include "GameState.h"
#include "Player.h"
Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Save(ofstream& OutFile, GameObjectType type) {  //shahd
	if (type != FLAG_TYPE) return;
	OutFile << position.GetCellNum() << endl;
}

void Flag::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition(cellNum);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click

	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that
	
	pGrid->PrintErrorMessage("You have reached a flag. Click to continue ...");

	pState->SetEndGame(true);

	pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " wins! Click to continue ...");
}

Flag::~Flag()
{

}