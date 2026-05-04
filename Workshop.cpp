#include "Workshop.h"
#include "Player.h"

Workshop::Workshop(const CellPosition &workshopPosition)
    : GameObject(workshopPosition) {}

void Workshop::Draw(Output *pOut) const { pOut->DrawWorkshop(position); }

void Workshop::Save(ofstream &OutFile, GameObjectType type) { // shahd
  if (type != WORKSHOP_TYPE)
    return;
  OutFile << position.GetCellNum() << endl;
}

void Workshop::Load(ifstream &Infile) {
  int cellNum;
  Infile >> cellNum;
  position = CellPosition(cellNum);
}

void Workshop::Apply(Grid *pGrid, GameState *pState, Player *pPlayer) {
  /// TODO: Implement this function
  // Apply the workshop's effect on the player
  // [OPTIONAL BONUS] Consumables can be given to the player here
  Output *pOut = pGrid->GetOutput();
  Input *pIn = pGrid->GetInput();

  // 1- Always repair 1 HP if possible
  if (pPlayer->GetHealth() < 10) {
    pPlayer->SetHealth(pPlayer->GetHealth() + 1);
    pGrid->PrintErrorMessage(
        "Workshop auto-repair: +1 HP! Click to continue...");
  } else {
    pGrid->PrintErrorMessage(
        "Workshop: You are already at max health! Click to continue...");
  }

  // 2- Choose bonus weapon or consumable
  pOut->PrintMessage("Workshop Bonus! Enter 1: Ext.Memory, 2: Toolkit, 3: Hack "
                     "Device, 4: Double Laser, 5: Skip");
  int choice = pIn->GetInteger(pOut);

  switch (choice) {
  case 1:
    pPlayer->SetExtendedMemory(true);
    pGrid->PrintErrorMessage("Equipped Extended Memory! Click to continue...");
    break;
  case 2:
    pPlayer->SetToolkit(true);
    pGrid->PrintErrorMessage("Equipped Toolkit! Click to continue...");
    break;
  case 3:
    pPlayer->SetHackDevice(true);
    pGrid->PrintErrorMessage("Equipped Hack Device! Click to continue...");
    break;
  case 4:
    pPlayer->SetLaserDamage(2);
    pGrid->PrintErrorMessage("Equipped Double Laser! Click to continue...");
    break;
  case 5:
    pGrid->PrintErrorMessage("No bonus selected. Click to continue...");
    break;
  default:
    pGrid->PrintErrorMessage("Invalid choice. Click to continue...");
    break;
  }
}

Workshop::~Workshop() {}
