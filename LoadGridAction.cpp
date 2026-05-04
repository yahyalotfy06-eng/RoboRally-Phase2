#include "LoadGridAction.h"
#include <fstream>
#include "AddAntennaAction.h"
#include "AddFlagAction.h"
#include "Antenna.h"
#include "Flag.h"
#include "WaterPit.h"
#include "DangerZone.h"
#include "Belt.h"
#include "Workshop.h"
#include "RotatingGear.h"
#include "Grid.h"

LoadGridAction::LoadGridAction(ApplicationManager *pApp) : Action(pApp) {
  ArrOrderTypes[0] = FLAG_TYPE;
  ArrOrderTypes[1] = WATERPIT_TYPE;
  ArrOrderTypes[2] = DANGERZONE_TYPE;
  ArrOrderTypes[3] = BELT_TYPE;
  ArrOrderTypes[4] = WORKSHOP_TYPE;
  ArrOrderTypes[5] = ANTENNA_TYPE;
  ArrOrderTypes[6] = ROTATINGGEAR_TYPE;
}
void LoadGridAction::ReadActionParameters() {
  // pointer to input & output
  Grid *pGrid = pManager->GetGrid();
  Output *pOut = pGrid->GetOutput();
  Input *pIn = pGrid->GetInput();

  // read file name
  pOut->PrintMessage("Enter file name load from: ");
  fileName = pIn->GetSrting(pOut);

  // clear msgs
  pOut->ClearStatusBar();
}

void LoadGridAction::Execute() {
  Grid *pGrid = pManager->GetGrid();
  ReadActionParameters();
  ifstream fileIn(fileName);

  if (!fileIn.is_open()) {
    pGrid->PrintErrorMessage("Error: cannot open file. Click to continue...");
    return;
  }

  // Reset static flags before loading
  AddAntennaAction::resetisantenna();
  AddFlagAction::resetisflag();

  // clear grid before loading
  pGrid->ClearGrid();
  
  for (int i = 0; i < 7; i++) {
    GameObjectType type = ArrOrderTypes[i];
    int count = 0;
    fileIn >> count;
    for (int j = 0; j < count; ++j) {
      GameObject *pObject = CreateObject(type);
      if (pObject != nullptr) {
        pObject->Load(fileIn);
        bool added = pGrid->AddObjectToCell(pObject);
        if (added) {
            if (type == ANTENNA_TYPE) AddAntennaAction::isAntennaAdded = true;
            if (type == FLAG_TYPE) AddFlagAction::isFlagAdded = true;
        } else {
            delete pObject; // Clean up if not added
        }
      }
    }
  }
  fileIn.close();

  // Redraw the board so all loaded objects appear on screen immediately
  pGrid->UpdateInterface(pManager->GetGameState());
}

GameObject *LoadGridAction::CreateObject(GameObjectType type) {

  GameObject *pObject = nullptr;
  switch (type) {
  case FLAG_TYPE:
    pObject = new Flag(CellPosition());
    break;

  case WATERPIT_TYPE:
    pObject = new WaterPit(CellPosition());
    break;

  case DANGERZONE_TYPE:
    pObject = new DangerZone(CellPosition());
    break;

  case BELT_TYPE:
    pObject = new Belt(CellPosition(), CellPosition());
    break;

  case WORKSHOP_TYPE:
    pObject = new Workshop(CellPosition());
    break;

  case ANTENNA_TYPE:
    pObject = new Antenna(CellPosition());
    break;

  case ROTATINGGEAR_TYPE:
    pObject = new RotatingGear(CellPosition(), false);
    break;

  default:
    break;
  }

  return pObject;
}

LoadGridAction::~LoadGridAction() {}