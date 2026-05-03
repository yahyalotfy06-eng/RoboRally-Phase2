#include "Workshop.h"
#include "Player.h"

Workshop::Workshop(const CellPosition &workshopPosition)
    : GameObject(workshopPosition) {}

void Workshop::Draw(Output *pOut) const { pOut->DrawWorkshop(position); }

void Workshop::Save(ofstream& OutFile, GameObjectType type) {  //shahd
    if (type != WORKSHOP_TYPE) return;
    OutFile << position.GetCellNum()<< endl;
}

void Workshop::Load(ifstream& Infile)
{
    int cellNum;
    Infile >> cellNum;
    position = CellPosition(cellNum);
}

void Workshop::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {
  /// TODO: Implement this function
  // Apply the workshop's effect on the player
  // [OPTIONAL BONUS] Consumables can be given to the player here
  Output* pOut = pGrid->GetOutput();
  Input* pIn = pGrid->GetInput();

  pOut->PrintMessage("Workshop! Enter 1: Repair(1HP), 2: Ext.Memory, 3: Toolkit, 4: Hack Device, 5: Double Laser");
  int choice = pIn->GetInteger(pOut);

  switch(choice) {
    case 1:
      if (pPlayer->GetHealth() < 10) { 
        pPlayer->SetHealth(pPlayer->GetHealth() + 1);
        pGrid->PrintErrorMessage("Repaired 1 HP. Click to continue...");
      } else {
        pGrid->PrintErrorMessage("Player is already at max health. Click to continue...");
      }
      break;
    case 2:
      pPlayer->SetExtendedMemory(true);
      pGrid->PrintErrorMessage("Purchased Extended Memory! Click to continue...");
      break;
    case 3:
      pPlayer->SetToolkit(true);
      pGrid->PrintErrorMessage("Purchased Toolkit! Click to continue...");
      break;
    case 4:
      pPlayer->SetHackDevice(true);
      pGrid->PrintErrorMessage("Purchased Hack Device! Click to continue...");
      break;
    case 5:
      pPlayer->SetLaserDamage(2);
      pGrid->PrintErrorMessage("Purchased Double Laser! Click to continue...");
      break;
    default:
      pGrid->PrintErrorMessage("Invalid choice. Click to continue...");
      break;
  }
}

Workshop::~Workshop() {}



