#include "RotatingGear.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"




RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Save(ofstream& OutFile, GameObjectType type) {  //shahd
	if (type != ROTATINGGEAR_TYPE) return;
	OutFile << position.GetCellNum()<< " "<< (int)isClockWise <<endl; //int converts bool to int (1 or 0)
}

void RotatingGear::Load(ifstream& Infile)
{
	int cellNum, cw;
	Infile >> cellNum >> cw;
	position = CellPosition(cellNum);
	isClockWise = (bool)cw;
}


void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	string rotationText = isClockWise ? "clockwise" : "anti-clockwise";
	pGrid->PrintErrorMessage("You have reached a rotating gear, you will rotate (" + rotationText + "). Click to continue ...");

	//2- Apply the roating gear's effect by rotating the player according to the direction
	Direction curr = pPlayer->GetDirection();
	Direction next = curr;

	if (isClockWise)
	{
		switch (curr)
		{
		case UP:    next = RIGHT; break;
		case RIGHT: next = DOWN;  break;
		case DOWN:  next = LEFT;  break;
		case LEFT:  next = UP;    break;
		}
	}
	else // anti-clockwise
	{
		switch (curr)
		{
		case UP:    next = LEFT;  break;
		case LEFT:  next = DOWN;  break;
		case DOWN:  next = RIGHT; break;
		case RIGHT: next = UP;    break;
		}
	}

	pPlayer->ClearDrawing(pGrid->GetOutput()); // erase old arrow direction
	pPlayer->SetDirection(next);
	pPlayer->Draw(pGrid->GetOutput());         // redraw with new direction
	pGrid->UpdateInterface(pState);
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

RotatingGear::~RotatingGear()
{
}
