#include "Belt.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"

Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Belt::Save(ofstream& OutFile, GameObjectType type) {  //shahd
	if (type != BELT_TYPE) return;
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}


void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click

	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	if (!endCellPos.IsValidCell())
		return;
	
	pGrid->PrintErrorMessage("You have reached a belt. Click to continue ...");//step 1-----


	pGrid->UpdatePlayerCell(pPlayer, endCellPos);//step 2-----


	pGrid->UpdateInterface(pState);//chose update interface function-----

}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}


Belt::~Belt() {}
