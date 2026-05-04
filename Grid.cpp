#include "Grid.h"
#include "Belt.h"
#include "Cell.h"
#include "GameObject.h"
#include "GameState.h"
#include "Player.h"
#include "Antenna.h"

Grid::Grid(Input *pIn, Output *pOut) : pIn(pIn), pOut(pOut) {
  // Allocate every Cell on the board (bottom-up so cell numbers are assigned
  // correctly)
  for (int i = NumVerticalCells - 1; i >= 0; i--)
    for (int j = 0; j < NumHorizontalCells; j++)
      CellList[i][j] = new Cell(i, j);

  Clipboard = NULL;
}

void Grid::saveAll(ofstream &OutFile, GameObjectType type) { // shahd
  for (int i = NumVerticalCells - 1; i >= 0; i--) {
    for (int j = 0; j < NumHorizontalCells; j++) {
      GameObject *pObject = CellList[i][j]->GetGameObject();
      if (pObject != nullptr) {
        pObject->Save(OutFile, type); // save is called depend on obj type
      }
    }
  }
}

void Grid::ClearGrid() {
  for (int i = 0; i < NumVerticalCells; i++) {
    for (int j = 0; j < NumHorizontalCells; j++) {
      if (CellList[i][j]->GetGameObject() != nullptr) {
        RemoveObjectFromCell(CellPosition(i, j));
      }
    }
  }
}

// ========== Board Operations ==========

bool Grid::AddObjectToCell(GameObject *pNewObject) {
  CellPosition start = pNewObject->GetPosition();

  if (!start.IsValidCell() || start.GetCellNum() == 1)
    return false;

  Belt *belt = dynamic_cast<Belt *>(pNewObject);

  // ===== CASE 1: BELT =====
  if (belt) {
    CellPosition end = belt->GetEndPosition();
    if (!end.IsValidCell()) return false;

    int startH = start.HCell();
    int startV = start.VCell();
    int endH = end.HCell();
    int endV = end.VCell();

    int dh = (endH > startH) ? 1 : (endH < startH ? -1 : 0);
    int dv = (endV > startV) ? 1 : (endV < startV ? -1 : 0);

    int h = startH;
    int v = startV;

    // 🔴 CHECK ALL CELLS FIRST
    while (true) {
      CellPosition pos(v, h);
      
      // If ANY belt occupies this cell, or it's cell 1, return false
      if (IsCellOccupiedByBelt(pos) || pos.GetCellNum() == 1)
        return false;

      // Also check if any non-belt object occupies the cells
      GameObject* pObj = CellList[v][h]->GetGameObject();
      if (pObj != nullptr)
        return false;

      if (h == endH && v == endV)
        break;

      h += dh;
      v += dv;
    }

    // 🟢 store ONLY in start cell
    if (CellList[startV][startH]->GetGameObject() != nullptr)
      return false;

    CellList[startV][startH]->SetGameObject(pNewObject);
    return true;

    return true;
  }

  // ===== CASE 2: NORMAL OBJECT =====
  GameObject *pPrevObject =
      CellList[start.VCell()][start.HCell()]->GetGameObject();

  if (pPrevObject)
    return false;

  CellList[start.VCell()][start.HCell()]->SetGameObject(pNewObject);
  return true;
}

// as objs were created by new in actions, f we need to delete them 3shan el
// memory

void Grid::RemoveObjectFromCell(const CellPosition &pos) {
  if (!pos.IsValidCell()) // prevention of accessing invalid loc
    return;
  Cell *pCell =
      CellList[pos.VCell()][pos.HCell()]; // accessing the needed cell in gird

  GameObject *pObj = pCell->GetGameObject(); // points to obj inside cell
  // check existance of obj to delete.
  if (pObj) // making sure cell has smth in
  {
    delete pObj;                // free memory
    pCell->SetGameObject(NULL); // removes the cell pointer
  }
}

void Grid::UpdatePlayerCell(Player *player, const CellPosition &newPosition) {
  player->ClearDrawing(pOut);
  Cell *newCell = CellList[newPosition.VCell()][newPosition.HCell()];
  player->SetCell(newCell);
  player->Draw(pOut);
}

Belt *Grid::GetNextBelt(const CellPosition &position) {
  int startH = position.HCell();
  for (int i = position.VCell(); i >= 0; i--) {
    for (int j = startH; j < NumHorizontalCells; j++) {
      Belt *b = dynamic_cast<Belt *>(CellList[i][j]->GetGameObject());
      if (b)
        return b;
    }
    startH = 0; // next rows start from leftmost column
  }
  return NULL; // not found
}

bool Grid::IsCellOccupiedByBelt(const CellPosition &pos) {
  if (!pos.IsValidCell())
    return false;

  // Iterate through ALL cells to find belts
  for (int i = 0; i < NumVerticalCells; i++) {
    for (int j = 0; j < NumHorizontalCells; j++) {
      GameObject *pObj = CellList[i][j]->GetGameObject();
      Belt *pBelt = dynamic_cast<Belt *>(pObj);
      if (pBelt) {
        CellPosition start = pBelt->GetPosition();
        CellPosition end = pBelt->GetEndPosition();

        int sH = start.HCell(), sV = start.VCell();
        int eH = end.HCell(), eV = end.VCell();
        int pH = pos.HCell(), pV = pos.VCell();

        // Check if pH, pV is between start and end
        if (sH == eH && pH == sH) { // Vertical belt
          int minY = (sV < eV) ? sV : eV;
          int maxY = (sV < eV) ? eV : sV;
          if (pV >= minY && pV <= maxY)
            return true;
        } else if (sV == eV && pV == sV) { // Horizontal belt
          int minX = (sH < eH) ? sH : eH;
          int maxX = (sH < eH) ? eH : sH;
          if (pH >= minX && pH <= maxX)
            return true;
        }
      }
    }
  }
  return false;
}

// ========== Setters / Getters ==========

Input *Grid::GetInput() const { return pIn; }
Output *Grid::GetOutput() const { return pOut; }

void Grid::SetClipboard(GameObject *gameObject) {
  if (Clipboard) delete Clipboard;
  Clipboard = gameObject;
} // to be used in copy/cut
GameObject *Grid::GetClipboard() const {
  return Clipboard;
} // to be used in paste

Cell *Grid::GetStartCell() const {
  // Players start at the bottom-left cell of the board
  return CellList[NumVerticalCells - 1][0];
}

Antenna *Grid::GetAntenna() const {
  for (int i = 0; i < NumVerticalCells; i++) {
    for (int j = 0; j < NumHorizontalCells; j++) {
      Antenna *pAntenna = CellList[i][j]->HasAntenna();
      if (pAntenna)
        return pAntenna;
    }
  }
  return nullptr;
}
Cell *Grid::GetCell(const CellPosition &pos) const {
  if (!pos.IsValidCell())
    return nullptr;

  return CellList[pos.VCell()][pos.HCell()];
}

bool Grid::IsCellEmpty(const CellPosition &pos) const {
  Cell *pCell = GetCell(pos);
  if (!pCell)
    return false;

  return (pCell->GetGameObject() == nullptr);
}

// ========== User Interface ==========

void Grid::UpdateInterface(const GameState *pState) const {
  if (UI.InterfaceMode == MODE_DESIGN) {
    // 1- Draw every cell (background colour, water pits, danger zones)
    for (int i = NumVerticalCells - 1; i >= 0; i--)
      for (int j = 0; j < NumHorizontalCells; j++)
        CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);

    // 2- Draw other game objects on top (belts, flags, gears, etc.)
    for (int i = NumVerticalCells - 1; i >= 0; i--)
      for (int j = 0; j < NumHorizontalCells; j++)
        CellList[i][j]->DrawGameObject(pOut);

    // 3- Draw all player tokens (delegated to GameState -- Grid does not own
    // players)
    pState->DrawAllPlayers(pOut);
  } else // Play mode
  {
    // Print the players info bar on the right side of the toolbar.
    // GameState builds the string because it owns the player data.
    string playersInfo = "";
    pState->AppendPlayersInfo(playersInfo);
    pOut->PrintPlayersInfo(playersInfo);

    // Redraw the commands bar: saved commands (left) + available commands
    // (right)
    Player *pCurrent = pState->GetCurrentPlayer();
    if (pCurrent) {
      // Build saved commands array from the current player
      int savedCount = pCurrent->GetSavedCommandCount();
      Command savedCmds[MaxSavedCommands];
      for (int i = 0; i < savedCount; i++)
        savedCmds[i] = pCurrent->GetSavedCommand(i);

      // Get available commands from GameState
      int availCount = pState->GetAvailableCommandsCount();
      Command availCmds[MaxAvailableCommands];
      for (int i = 0; i < availCount; i++)
        availCmds[i] = pState->GetAvailableCommand(i);

      pOut->CreateCommandsBar(savedCmds, savedCount, availCmds, availCount);
    }

    // Note: UpdatePlayerCell() already redraws players step-by-step during Play
    // mode.
  }
}

void Grid::PrintErrorMessage(string msg) {
  pOut->PrintMessage(msg);
  int x, y;
  pIn->GetPointClicked(x, y);
  pOut->ClearStatusBar();
}

Grid::~Grid() {
  delete pIn;
  delete pOut;

  for (int i = NumVerticalCells - 1; i >= 0; i--)
    for (int j = 0; j < NumHorizontalCells; j++)
      delete CellList[i][j];

  // Players are owned by GameState -- do NOT delete them here.
}
// query
int Grid::GetCellTypeCount(GameObjectType type) { // shahd
  int count = 0;
  for (int i = NumVerticalCells - 1; i >= 0; i--)
    for (int j = 0; j < NumHorizontalCells; j++) {
      switch (type) {
      case FLAG_TYPE:
        if (CellList[i][j]->HasFlag() != nullptr) {
          ++count;
        }
        break;
      case WATERPIT_TYPE:
        if (CellList[i][j]->HasWaterPit() != nullptr) {
          ++count;
        }
        break;
      case DANGERZONE_TYPE:
        if (CellList[i][j]->HasDangerZone() != nullptr) {
          ++count;
        }
        break;
      case BELT_TYPE:
        if (CellList[i][j]->HasBelt() != nullptr) {
          ++count;
        }
        break;
      case WORKSHOP_TYPE:
        if (CellList[i][j]->HasWorkshop() != nullptr) {
          ++count;
        }
        break;
      case ANTENNA_TYPE:
        if (CellList[i][j]->HasAntenna() != nullptr) {
          ++count;
        }
        break;
      case ROTATINGGEAR_TYPE:
        if (CellList[i][j]->HasRotatingGear() != nullptr) {
          ++count;
        }
        break;
      default:
        break;
      }
    }

  return count;
}