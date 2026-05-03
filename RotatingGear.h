#pragma once
#include "GameObject.h"
#include <fstream>
#include "DEFS.h"
class RotatingGear : public GameObject
{
	bool isClockWise; // if it is true then direction is clockwise, if it is false then direction is anticlockwise
public:
	RotatingGear(const CellPosition & gearposition,bool clockwise); // A constructor for initialization
	virtual GameObject* Clone() const override { return new RotatingGear(*this); }
	virtual void Draw(Output* pOut) const; // Draws a rotating gear in a selected cell
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the rotating gear
	bool GetisClockWise() const; // Getter for the direction

	virtual void Save(ofstream& OutFile, GameObjectType type) override;
	virtual void Load(ifstream& Infile) override;

	virtual ~RotatingGear();
};

