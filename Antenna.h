#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class Antenna :public GameObject
{
public:
	Antenna(const CellPosition & antennaPosition); // A constructor for initialization
	virtual GameObject* Clone() const override { return new Antenna(*this); }
	virtual void Draw(Output* pOut) const; // Draws an antenna

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the antenna

	virtual void Save(ofstream& OutFile, GameObjectType type) override;       //shahd
	virtual void Load(ifstream& Infile) override;

	virtual ~Antenna();
};
