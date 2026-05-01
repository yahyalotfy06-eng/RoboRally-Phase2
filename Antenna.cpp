#include "Antenna.h"
#include "GameState.h"
#include "Player.h"
#include <cmath>




Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Save(ofstream& OutFile, GameObjectType type) {  //shahd
    if (type != ANTENNA_TYPE) return;
    OutFile << position.GetCellNum() << endl;
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	// 3- Print a message indicating which player will play first



    pGrid->PrintErrorMessage("The antenna will decide the turn of players. Click to continue ...");//step 1-----yahya



    CellPosition antennaPos = this->GetPosition();

    int bestPlayer = -1;
    int bestDistance = 999999; 

   
    for (int i = 0; i < MaxPlayerCount; i++)
    {
        Player* p = pState->GetPlayer(i);
        CellPosition playerPos = p->GetCell()->GetCellPosition();

        int dV = abs(playerPos.VCell() - antennaPos.VCell());
        int dH = abs(playerPos.HCell() - antennaPos.HCell());

        int distance = dV + dH;


        if (distance < bestDistance)
        {
            bestDistance = distance;
            bestPlayer = i;
        }
    }

 
    pState->SetFirstPlayer(bestPlayer);//step 2-----yahya

    
    pGrid->PrintErrorMessage("Player " + to_string(bestPlayer) + " will play first!");//step 3-----yahya



}


Antenna::~Antenna()
{
}
