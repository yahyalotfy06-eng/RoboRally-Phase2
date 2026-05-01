#include "Player.h"

#include "GameObject.h"
#include "GameState.h"

Player::Player(Cell *pCell, int playerNum)
    : playerNum(playerNum), health(10), currDirection(RIGHT),
      savedCommandCount(0) {
  this->pCell = pCell;

  // Initialise saved commands to NO_COMMAND
  for (int i = 0; i < MaxSavedCommands; i++)
    savedCommands[i] = NO_COMMAND;
}

// ====== Setters and Getters ======

void Player::SetCell(Cell *cell) { pCell = cell; }
Cell *Player::GetCell() const { return pCell; }

void Player::SetHealth(int h) {
  /// TODO: Add validation (e.g. clamp to 0..MaxHealth)
  if (h < 0)  h = 0;   // clamp: health cannot go below 0
  if (h > 10) h = 10;  // clamp: health cannot exceed max (10)
  health = h;
}
int Player::GetHealth() const { return health; }

Direction Player::GetDirection() const { return currDirection; }
void Player::SetDirection(Direction d) { currDirection = d; }

// ====== Saved Commands ======

void Player::AddSavedCommand(Command cmd) {
  if (savedCommandCount < MaxSavedCommands)
    savedCommands[savedCommandCount++] = cmd;
}

void Player::ClearSavedCommands() {
  for (int i = 0; i < MaxSavedCommands; i++)
    savedCommands[i] = NO_COMMAND;
  savedCommandCount = 0;
}

int Player::GetSavedCommandCount() const { return savedCommandCount; }
Command Player::GetSavedCommand(int index) const {
  if (index >= 0 && index < savedCommandCount)
    return savedCommands[index];
  return NO_COMMAND;
}

// ====== Drawing Functions ======

void Player::Draw(Output *pOut) const {
  color playerColor = UI.PlayerColors[playerNum];

  pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor,
                   currDirection);
  /// TODO: Call the appropriate Output function to draw the player token with
  /// playerColor
}

void Player::ClearDrawing(Output *pOut) const {
  /// TODO: Determine the correct background colour for this cell
  //       (hint: may differ from UI.CellColor if cell is a WaterPit or
  //       DangerZone)
  color cellColor = UI.CellColor;

  if (pCell->HasWaterPit()) {
    cellColor = UI.WaterPitsCellColor;
  }

  if (pCell->HasDangerZone()) {
    cellColor = UI.DangerZoneCellColor;
  }

  pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor,
                   currDirection);

  /// TODO: Call the appropriate Output function to draw the token using
  /// cellColor (erases it)
}

void Player::ResetPlayer(Grid* pGrid)
{
    // Reset player to start cell
    Cell* pStartCell = pGrid->GetStartCell();
    SetCell(pStartCell);

    // Reset health to 10
    SetHealth(10);

    // Reset direction to RIGHT
    SetDirection(RIGHT);

    // Clear commands
    ClearSavedCommands();
}

// ====== Game Logic ======

void Player::Move(Grid *pGrid, GameState *pState) {
  /// TODO: Implement this function
  // - Execute the saved commands one by one, waiting for a mouse click between
  // each
  // - After all commands are executed, apply the game object effect at the
  // final cell (if any)
  // - Use CellPosition and Grid to handle movement and cell updates

  for (int i = 0; i < savedCommandCount; i++) {
    Command cmd = savedCommands[i];

    if (cmd == NO_COMMAND)
      continue;

    int steps = 0;
    bool backward = false;

    switch (cmd) // choose which command to be executed-----yahya
    {
    case MOVE_FORWARD_ONE_STEP:
      steps = 1;
      break;
    case MOVE_BACKWARD_ONE_STEP:
      steps = 1;
      backward = true;
      break;
    case MOVE_FORWARD_TWO_STEPS:
      steps = 2;
      break;
    case MOVE_BACKWARD_TWO_STEPS:
      steps = 2;
      backward = true;
      break;
    case MOVE_FORWARD_THREE_STEPS:
      steps = 3;
      break;
    case MOVE_BACKWARD_THREE_STEPS:
      steps = 3;
      backward = true;
      break;
    case ROTATE_CLOCKWISE:
      switch (currDirection) { // calculate the upcoming direction after
                               // rotation-----yahya
      case UP:
        currDirection = RIGHT;
        break;
      case RIGHT:
        currDirection = DOWN;
        break;
      case DOWN:
        currDirection = LEFT;
        break;
      case LEFT:
        currDirection = UP;
        break;
      }
      break;
    case ROTATE_COUNTERCLOCKWISE:
      switch (currDirection) {
      case UP:
        currDirection = LEFT;
        break;
      case LEFT:
        currDirection = DOWN;
        break;
      case DOWN:
        currDirection = RIGHT;
        break;
      case RIGHT:
        currDirection = UP;
        break;
      }
      break;
    }

    if (steps > 0) {
      Direction moveDir = currDirection;
      if (backward) {
        switch (currDirection) {
        case UP:
          moveDir = DOWN;
          break;
        case DOWN:
          moveDir = UP;
          break;
        case RIGHT:
          moveDir = LEFT;
          break;
        case LEFT:
          moveDir = RIGHT;
          break;
        }
      }

      for (int s = 0; s < steps; s++) {
        CellPosition currentPos = pCell->GetCellPosition();
        currentPos.AddCellNum(1, moveDir);

        if (!currentPos.IsValidCell()) {//check if player fell off the grid-----yahya
          pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " fell off the board! Rebooting...");
          SetHealth(health - 1); // use SetHealth so the 0..10 clamp is always applied
          pGrid->UpdatePlayerCell(this, pGrid->GetStartCell()->GetCellPosition());
          return;
        }

        pGrid->UpdatePlayerCell(this, currentPos);



        GameObject* obj = pCell->GetGameObject();//execute any game object the player passes on-----yahya
        if (obj)
        {
            obj->Apply(pGrid, pState, this);
        }




        pGrid->UpdateInterface(pState);

        pGrid->PrintErrorMessage("Step executed. Click to continue...");
      }
    } else {
      this->ClearDrawing(pGrid->GetOutput());
      this->Draw(pGrid->GetOutput());
      pGrid->UpdateInterface(pState);

      pGrid->PrintErrorMessage("Rotation executed. Click to continue...");
    }
  }
}

void Player::AppendPlayerInfo(string &playersInfo) const {
  string dirText;
  switch (currDirection) {
  case UP:
    dirText = "Up";
    break;
  case DOWN:
    dirText = "Down";
    break;
  case RIGHT:
    dirText = "Right";
    break;
  case LEFT:
    dirText = "Left";
    break;
  }

  playersInfo += "P" + to_string(playerNum) + "(Dir: " + dirText +
                 ", Health: " + to_string(health) + ")";
}
