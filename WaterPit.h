#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterpitposition); // A constructor for initialization
	virtual GameObject* Clone() const override { return new WaterPit(*this); }
	virtual void Draw(Output* pOut) const; // Draws a water pit in a selected cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit

	virtual void Save(ofstream& OutFile, GameObjectType type) override;
	virtual void Load(ifstream& Infile) override;

	virtual ~WaterPit();
};

