#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class DangerZone:public GameObject
{
public:
	DangerZone(const CellPosition & dangerZonePosition);
	virtual void Draw(Output* pOut) const; // Draws a danger zone in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the danger zone

	virtual void Save(ofstream& OutFile, GameObjectType type) override;
	virtual void Load(ifstream& Infile) override;

	virtual ~DangerZone();
};

