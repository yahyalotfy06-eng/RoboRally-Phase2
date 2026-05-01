#include "LoadGridAction.h"
#include<fstream>

LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp) {

}
void LoadGridAction::ReadActionParameters() {
	//pointer to input & output
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//read file name
	pOut->PrintMessage("Enter file name load from: ");
	fileName = pIn->GetSrting(pOut);

	//clear msgs
	pOut->ClearStatusBar();
}

void LoadGridAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	ifstream fileIn(fileName);

	if (!fileIn.is_open()) {
		pGrid->PrintErrorMessage("Error: cannot open file. Click to continue...");
		return;
	}
	//clear grid
	for (int i = 0; i < 7; i++) {
		GameObjectType type = ArrOrderTypes[i];
		int count = 0;
		fileIn >> count;
		for (int j = 0; j < count; ++j) {
			GameObject* pObject = CreateObject(type);
			if (pObject != nullptr) {
				pObject->Load(fileIn);
				pGrid->AddObjectToCell(pObject);
			}
		}
	}
	fileIn.close();
}

GameObject* LoadGridAction::CreateObject(GameObjectType type) {

	GameObject* pObject = nullptr;
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

	default: break;
	}

	return pObject;

}

LoadGridAction::~LoadGridAction() {

}