#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"

// Workshop: a special cell that applies an effect on the player who lands on it.
// [OPTIONAL BONUS] Consumables can be added as an extension.
class Workshop : public GameObject
{
public:
	Workshop(const CellPosition & workshopPosition);
	virtual void Draw(Output* pOut) const; // Draws workshop

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the workshop

	virtual void Save(ofstream& OutFile, GameObjectType type) = 0;       //shahd
	virtual void Load(ifstream& Infile) = 0;

	~Workshop();
};

