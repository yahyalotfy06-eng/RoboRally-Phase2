#include "AddBeltAction.h"
#include "Grid.h"
#include "Belt.h"

AddBeltAction::AddBeltAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddBeltAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	while (!startPos.IsValidCell() || !endPos.IsValidCell() ||
		startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("Error: Invalid selection! Click to continue ...");
		pIn->GetCellClicked();

		pOut->PrintMessage("New Belt: Click on its Start Cell ...");
		startPos = pIn->GetCellClicked();

		pOut->PrintMessage("New Belt: Click on its End Cell ...");
		endPos = pIn->GetCellClicked();
	}

	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();

	// Only horizontal or vertical belts allowed
	if (startPos.HCell() != endPos.HCell() && startPos.VCell() != endPos.VCell())
	{
		pGrid->PrintErrorMessage("Error: Belt must be horizontal or vertical! Click to continue ...");
		return;
	}

	bool newHorizontal = (startPos.VCell() == endPos.VCell());

	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellPosition pos(i, j);
			GameObject* obj = pGrid->GetCell(pos)->GetGameObject();
			Belt* existing = dynamic_cast<Belt*>(obj);

			if (!existing) continue;

			CellPosition s = existing->GetPosition();
			CellPosition e = existing->GetEndPosition();

			bool existHorizontal = (s.VCell() == e.VCell());

			// -------- Horizontal belts --------
			if (newHorizontal && existHorizontal)
			{
				if (startPos.VCell() == s.VCell()) // same row
				{
					int newStart = min(startPos.HCell(), endPos.HCell());
					int newEnd = max(startPos.HCell(), endPos.HCell());

					int exStart = min(s.HCell(), e.HCell());
					int exEnd = max(s.HCell(), e.HCell());

					// reject overlap OR touching
					if (!(newEnd < exStart - 1 || exEnd < newStart - 1))
					{
						pGrid->PrintErrorMessage("Error: Belts cannot overlap or touch on the same row!");
						return;
					}
				}
			}

			// -------- Vertical belts --------
			else if (!newHorizontal && !existHorizontal)
			{
				if (startPos.HCell() == s.HCell()) // same column
				{
					int newStart = min(startPos.VCell(), endPos.VCell());
					int newEnd = max(startPos.VCell(), endPos.VCell());

					int exStart = min(s.VCell(), e.VCell());
					int exEnd = max(s.VCell(), e.VCell());

					// reject overlap OR touching
					if (!(newEnd < exStart - 1 || exEnd < newStart - 1))
					{
						pGrid->PrintErrorMessage("Error: Belts cannot overlap or touch on the same column!");
						return;
					}
				}
			}
		}
	}

	// Create belt
	Belt* pBelt = new Belt(startPos, endPos);

	bool added = pGrid->AddObjectToCell(pBelt);

	if (!added)
	{
		delete pBelt;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue ...");
		return;
	}
}

AddBeltAction::~AddBeltAction()
{
}