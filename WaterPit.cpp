#include "WaterPit.h"
#include "GameState.h"
#include "Player.h"

WaterPit::WaterPit(const CellPosition &waterPitPosition)
    : GameObject(waterPitPosition) {}

void WaterPit::Save(ofstream &OutFile, GameObjectType type) { // shahd
  if (type != WATERPIT_TYPE)
    return;
  OutFile << position.GetCellNum() << endl;
}

void WaterPit::Load(ifstream &Infile) {
  int cellNum;
  Infile >> cellNum;
  position = CellPosition(cellNum);
}

void WaterPit::Draw(Output *pOut) const { pOut->DrawWaterPit(position); }

void WaterPit::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {

  /// TODO: Implement this function as mentioned in the guideline steps
  /// (numbered below) below

  // == Here are some guideline steps (numbered below) to implement this
  // function ==

  // 1- Print a message indicating the player fell into the water pit.
  pGrid->PrintErrorMessage("You fell in a water pit! You lose 3 HP and reboot. Click to continue ...");

  // 2- Apply the water pit's effect by reducing health by 3 and returning to start cell
  int newHealth = pPlayer->GetHealth() - 3;
  if (newHealth < 0) newHealth = 0;
  pPlayer->SetHealth(newHealth);

  if (newHealth == 0) {
    pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " drowned! Game over. Click to continue...");
    pState->SetEndGame(true);
  } else {
    pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());
  }

  // 3- Update the players info which is displayed (check Grid class and decide
  // which function to use)
  pGrid->UpdateInterface(pState);
}

WaterPit::~WaterPit() {}



