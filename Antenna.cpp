#include "Antenna.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"
#include <cmath>
#include <string>

using namespace std;

Antenna::Antenna(const CellPosition &antennaPosition)
    : GameObject(antennaPosition) {}

void Antenna::Save(ofstream &OutFile, GameObjectType type) { // shahd
  if (type != ANTENNA_TYPE)
    return;
  OutFile << position.GetCellNum() << endl;
}

void Antenna::Load(ifstream &Infile) // shahd
{
  int cellNum;
  Infile >> cellNum;
  position = CellPosition(cellNum);
}

void Antenna::Draw(Output *pOut) const { pOut->DrawAntenna(position); }

void Antenna::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {

  pGrid->PrintErrorMessage("The antenna will decide the turn of players. Click to continue ...");

  CellPosition antennaPos = this->GetPosition();

  struct PlayerDistance {
    int playerNum;
    int distance;
  };

  PlayerDistance distances[MaxPlayerCount];

  for (int i = 0; i < MaxPlayerCount; i++) {
    Player *p = pState->GetPlayer(i);
    CellPosition playerPos = p->GetCell()->GetCellPosition();

    // Manhattan distance: |dV| + |dH|
    int dV = abs(playerPos.VCell() - antennaPos.VCell());
    int dH = abs(playerPos.HCell() - antennaPos.HCell());
    
    distances[i].playerNum = i;
    distances[i].distance = dV + dH;
  }

  // Sort players by distance, then by player number (tie-breaker)
  // Using a simple Bubble Sort for MaxPlayerCount (4)
  for (int i = 0; i < MaxPlayerCount - 1; i++) {
    for (int j = 0; j < MaxPlayerCount - i - 1; j++) {
      if (distances[j].distance > distances[j+1].distance || 
         (distances[j].distance == distances[j+1].distance && distances[j].playerNum > distances[j+1].playerNum)) {
        PlayerDistance temp = distances[j];
        distances[j] = distances[j+1];
        distances[j+1] = temp;
      }
    }
  }

  int order[MaxPlayerCount];
  for (int i = 0; i < MaxPlayerCount; i++) {
    order[i] = distances[i].playerNum;
  }

  pState->SetPlayerOrder(order);

  pGrid->PrintErrorMessage("Player " + to_string(order[0]) + " will play first!");
}

Antenna::~Antenna() {}
