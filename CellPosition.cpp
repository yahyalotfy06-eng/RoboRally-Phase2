#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	//valid range from 0 to NumVerticalCells - 1
	if (v >= 0 && v < NumVerticalCells)
	{
		vCell = v;
		return true;

	}
	else {
		return false; // this line sould be changed with your implementation
	}
}

bool CellPosition::SetHCell(int h) 

{
	//valid range from 0 to NumHorizontalCells - 1
	if (h >= 0 && h < NumHorizontalCells)
	{
		hCell = h;
		return true;
	} else {
		return false; // this line sould be changed with your implementation
	}
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (vCell >= 0 && vCell < NumVerticalCells) {
		if (hCell >= 0 && hCell < NumHorizontalCells)
		{
			return true;
		}
	}
	return false;
}
int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}



int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it
	if (!cellPosition. IsValidCell())
	{
		return -1;
	}
	int h = cellPosition.HCell(); //get column
	int v = cellPosition.VCell(); //get row
	int rowflip = (NumVerticalCells - 1) - v; //row flipping
	int cellnuum = (rowflip * NumHorizontalCells) + h + 1;
	


	return cellnuum; // this line should be changed with your implementation
}



CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if (cellNum < 1 || cellNum > (NumVerticalCells * NumHorizontalCells))
		return CellPosition(-1, -1);
	//inverse of the above function
	//position from bottom
	int Obased = cellNum - 1; //0 based 
	int rowfmtop = Obased / NumHorizontalCells;
	int col = Obased % NumHorizontalCells;
	//flip to be from bottom
	int vCell = (NumVerticalCells - 1) - rowfmtop;
	int hCell = col;
	return CellPosition(vCell, hCell);

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
{
	// Note: this function updates the data members (vCell and hCell) of the calling object
	switch (direction) {
	case UP:
		vCell = vCell - addedNum;
		break;
	case DOWN:
		vCell = vCell + addedNum;
		break;
	case RIGHT:
		hCell = hCell + addedNum;
		break;
	case LEFT:
		hCell = hCell - addedNum;
		break;
	}
	if (!IsValidCell())
	{
		vCell = -1;
		hCell = -1;
	}
}