#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterPitPosition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit

	virtual void Save(ofstream& OutFile, GameObjectType type) = 0;       //shahd
	virtual void Load(ifstream& Infile) = 0;

	virtual ~WaterPit();
};

