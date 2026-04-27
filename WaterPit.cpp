#include "WaterPit.h"
#include "GameState.h"
#include "Player.h"

WaterPit::WaterPit(const CellPosition &waterPitPosition)
    : GameObject(waterPitPosition) {}

void WaterPit::Draw(Output *pOut) const { pOut->DrawWaterPit(position); }

void WaterPit::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {

  /// TODO: Implement this function as mentioned in the guideline steps
  /// (numbered below) below

  // == Here are some guideline steps (numbered below) to implement this
  // function ==

  // 1- Print a message, make sure to edit this message according to which
  // player wins "You drowned in a water pit. Player (0/1) wins !  Click to
  // continue ..." and wait mouse click
  int winnerNum = -1;
  for (int i = 0; i < MaxPlayerCount; i++)
  {
    if (pState->GetPlayer(i) != pPlayer)
    {
      winnerNum = i;
      break;
    }
  }
  string msg = "You drowned in a water pit. Player " + to_string(winnerNum) + " wins!  Click to continue ...";
  pGrid->PrintErrorMessage(msg);

  // 2- Apply the water pit's effect by setting the player's health which
  // drowned to zero and ending the game
  pPlayer->SetHealth(0);
  pState->SetEndGame(true);

  // 3- Update the players info which is displayed (check Grid class and decide which function to use)
  pGrid->UpdateInterface(pState);
}

WaterPit::~WaterPit() {}
