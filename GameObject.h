#pragma once

#include "Grid.h"

// Forward declarations
class Player;
class GameState;

// Base class for all game objects (Belt, Flag, WaterPit, DangerZone,
// RotatingGear, Workshop, Antenna).
class GameObject {
protected:
  CellPosition position; // The cell this object occupies

public:
  GameObject(const CellPosition &pos);

  CellPosition GetPosition() const;
  virtual void SetPosition(const CellPosition &pos) { position = pos; }

  // ============ Virtual Functions ============

  virtual GameObject* Clone() const = 0;

  virtual void Draw(Output *pOut) const = 0;

  virtual void Apply(Grid *pGrid, GameState *pState, Player *pPlayer) = 0;

  // Save / Load (uncomment and implement in derived classes when needed):
  virtual void Save(ofstream &OutFile, GameObjectType type) = 0; // shahd
  virtual void Load(ifstream &Infile) = 0;

  virtual ~GameObject();
};
