#include "Workshop.h"
#include "Player.h"

Workshop::Workshop(const CellPosition &workshopPosition)
    : GameObject(workshopPosition) {}

void Workshop::Draw(Output *pOut) const { pOut->DrawWorkshop(position); }

void Workshop::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {
  /// TODO: Implement this function
  // Apply the workshop's effect on the player
  // [OPTIONAL BONUS] Consumables can be given to the player here
  
  if (pPlayer->GetHealth() < 10) { 
    pPlayer->SetHealth(pPlayer->GetHealth() + 1);//apply workshop and increase health by 1-----yahya
    pGrid->PrintErrorMessage("Workshop applied! Player repaired 1 HP. Click to continue...");
  } else {
    pGrid->PrintErrorMessage("Workshop applied! Player is already at max health. Click to continue...");
  }
}

Workshop::~Workshop() {}
