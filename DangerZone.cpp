#include "DangerZone.h"
#include "GameState.h"
#include "Player.h"



DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Save(ofstream& OutFile, GameObjectType type) {  //shahd
	if (type != DANGERZONE_TYPE) return;
	OutFile << position.GetCellNum() << endl;
}

void DangerZone::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition(cellNum);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a danger zone. Click to continue ...");

	// 2- Apply the danger zone's effect by reducing the health of the player by 1
	int newHealth = pPlayer->GetHealth() - 1;
	if (newHealth < 0) newHealth = 0;        // clamp so health never goes negative
	pPlayer->SetHealth(newHealth);

	// if the player's health reached zero, the game ends
	if (newHealth == 0)
	{
		pGrid->PrintErrorMessage("A player has died from the Danger Zone! Game over. Click to continue ...");
		pState->SetEndGame(true);
	}

	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface(pState);
}


DangerZone::~DangerZone()
{
}



