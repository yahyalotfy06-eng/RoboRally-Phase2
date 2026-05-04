#pragma once
#include "Action.h"
#include "Antenna.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"

class AddAntennaAction : public Action {

  CellPosition antennaPosition;

public:
  static bool isAntennaAdded;
  AddAntennaAction(ApplicationManager *pApp);

  virtual void ReadActionParameters();

  virtual void Execute();

  static void resetisantenna();

  virtual ~AddAntennaAction();
};
