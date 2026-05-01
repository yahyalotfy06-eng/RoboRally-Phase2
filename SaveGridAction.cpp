
#include "SaveGridAction.h"
#include<fstream>
SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp) {

}
void SaveGridAction::ReadActionParameters() {
	//pointer to input & output
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//read file name
	pOut->PrintMessage("Enter file name to save to: ");
	fileName = pIn->GetSrting(pOut);

	//clear msgs
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	ofstream fileOut(fileName);

	if (!fileOut.is_open()) {
		pGrid->PrintErrorMessage("Error: cannot open file. Click to continue...");
		return;
}
	for (int i = 0; i < 7; i++) {
		GameObjectType type = ArrOrderTypes[i];
		fileOut<<pGrid->GetCellTypeCount(type) << endl;
		pGrid->saveAll(fileOut, type);
	}
	fileOut.close();
}
SaveGridAction::~SaveGridAction() {
}