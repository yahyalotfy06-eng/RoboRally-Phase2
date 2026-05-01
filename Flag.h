#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class Flag :public GameObject
{
public:
	Flag(const CellPosition & flagposition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a flag in a selected cell
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the flag

	virtual void Save(ofstream& OutFile, GameObjectType type) = 0;       //shahd
	virtual void Load(ifstream& Infile) = 0;

	virtual ~Flag(); // Virtual destructor
};