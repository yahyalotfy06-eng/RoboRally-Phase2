#pragma once
#include "DEFS.h"
#include "GameObject.h"
#include <fstream>

class Flag : public GameObject {
public:
  Flag(const CellPosition &flagposition); // A constructor for initialization
  virtual void Draw(Output *pOut) const;  // Draws a flag in a selected cell
  virtual void Apply(Grid *pGrid, GameState *pState,
                     Player *pPlayer); // Applies the effect of the flag

  virtual void Save(ofstream &OutFile, GameObjectType type) override;
  virtual void Load(ifstream &Infile) override;

  virtual GameObject* Clone() const override { return new Flag(*this); }

  virtual ~Flag(); // Virtual destructor
};
