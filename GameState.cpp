#include "GameState.h"

#include "Cell.h"
#include "Grid.h"
#include "Output.h"
#include "Player.h"
#include <string>

GameState::GameState(Grid *pGrid) {
  // Create all Player objects starting at the board's designated start cell.
  // The Grid provides the start cell position; the GameState owns the Player
  // objects.
  Cell *startCell = pGrid->GetStartCell();
  Output *pOut = pGrid->GetOutput();

  for (int i = 0; i < MaxPlayerCount; i++) {
    PlayerList[i] = new Player(startCell, i);
    PlayerList[i]->Draw(pOut); // draw initial position
    playerOrder[i] = i;        // Default order: 0, 1, 2, 3
  }

  currentOrderIndex = 0;
  currPlayerNumber = playerOrder[currentOrderIndex]; 
  currentPhase = PHASE_MOVEMENT;
  endGame = false;
  availableCommandsCount = 0; // No available commands until Play Mode starts
}

GameState::~GameState() {
  for (int i = 0; i < MaxPlayerCount; i++)
    delete PlayerList[i];
}

// ========== Player Access ==========

Player *GameState::GetCurrentPlayer() const {
  return PlayerList[currPlayerNumber];
}

Player *GameState::GetPlayer(int playerNum) const {
  if (playerNum >= 0 && playerNum < MaxPlayerCount) {
    return PlayerList[playerNum];
  }
  return NULL;
}

// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer() {
  currentOrderIndex = (currentOrderIndex + 1) % MaxPlayerCount;
  currPlayerNumber = playerOrder[currentOrderIndex];
}

int GameState::GetCurrentOrderIndex() const { return currentOrderIndex; }

void GameState::SetPlayerOrder(const int order[]) {
  for (int i = 0; i < MaxPlayerCount; i++) {
    playerOrder[i] = order[i];
  }
  currentOrderIndex = 0;
  currPlayerNumber = playerOrder[currentOrderIndex];
}

void GameState::SetFirstPlayer(int playerNum) {
  if (playerNum >= 0 && playerNum < MaxPlayerCount) {
    for (int i = 0; i < MaxPlayerCount; i++) {
      playerOrder[i] = (playerNum + i) % MaxPlayerCount;
    }
    currentOrderIndex = 0;
    currPlayerNumber = playerOrder[currentOrderIndex];
  }
}

// ========== Phase Management ==========

PhaseType GameState::GetCurrentPhase() const { return currentPhase; }

void GameState::SetCurrentPhase(PhaseType phase) { currentPhase = phase; }

void GameState::AdvancePhase() {
  // Currently only PHASE_MOVEMENT exists.
  // [OPTIONAL BONUS] If you add PHASE_SHOOTING to the PhaseType enum (DEFS.h),
  // update this to cycle:  MOVEMENT --> SHOOTING --> MOVEMENT
  if (currentPhase == PHASE_MOVEMENT) currentPhase = PHASE_SHOOTING;
  else currentPhase = PHASE_MOVEMENT;
}

void GameState::ExecuteShootingPhase(Grid* pGrid) {
    SetCurrentPhase(PHASE_SHOOTING);

    // Loop through all players so everyone gets a chance to shoot
    for (int i = 0; i < MaxPlayerCount; i++) {
        Player* pShooter = PlayerList[i];
        if (!pShooter) continue;

        CellPosition shooterPos = pShooter->GetCell()->GetCellPosition();
        Direction shooterDir = pShooter->GetDirection();

        // Check against all other players (the opponents)
        for (int j = 0; j < MaxPlayerCount; j++) {
            if (i == j) continue; // Can't shoot yourself

            Player* pTarget = PlayerList[j];
            if (!pTarget) continue;

            CellPosition targetPos = pTarget->GetCell()->GetCellPosition();
            bool isHit = false;

            // Check alignment and direction
            if (shooterDir == UP && shooterPos.HCell() == targetPos.HCell() && targetPos.VCell() < shooterPos.VCell()) {
                isHit = true;
            } 
            else if (shooterDir == DOWN && shooterPos.HCell() == targetPos.HCell() && targetPos.VCell() > shooterPos.VCell()) {
                isHit = true;
            } 
            else if (shooterDir == RIGHT && shooterPos.VCell() == targetPos.VCell() && targetPos.HCell() > shooterPos.HCell()) {
                isHit = true;
            } 
            else if (shooterDir == LEFT && shooterPos.VCell() == targetPos.VCell() && targetPos.HCell() < shooterPos.HCell()) {
                isHit = true;
            }

            // Apply damage if hit
            if (isHit) {
                // Get damage (1 for Basic Laser, 2 if Double Laser was bought at Workshop)
                int damage = pShooter->GetLaserDamage(); 
                
                pTarget->SetHealth(pTarget->GetHealth() - damage);
                
                // Show exact message requested by the document
                pGrid->PrintErrorMessage("You hit another player, click to continue");
                
                // Optional: Check if target died
                if (pTarget->GetHealth() <= 0) {
                     pGrid->PrintErrorMessage("Player " + to_string(pTarget->GetPlayerNum()) + " was destroyed! Click to continue.");
                     SetEndGame(true);
                     return;
                }
            }
        }
    }
    
    AdvancePhase(); // Return to PHASE_MOVEMENT
}

// ========== End-Game ==========

bool GameState::GetEndGame() const { return endGame; }

void GameState::SetEndGame(bool end) { endGame = end; }

// ========== End-Game ==========

void GameState::ResetGame(Grid *pGrid) // shahd
{
  for (int i = 0; i < MaxPlayerCount; i++) {
    PlayerList[i]->ResetPlayer(pGrid);
    playerOrder[i] = i;
  }

  currentOrderIndex = 0;
  currPlayerNumber = playerOrder[currentOrderIndex];

  currentPhase = PHASE_MOVEMENT;

  endGame = false;

  availableCommandsCount = 0;
}

void GameState::DrawAllPlayers(Output *pOut) const {
  /// TODO: Draw all players
  for (int i = 0; i < MaxPlayerCount; i++) {
    PlayerList[i]->Draw(pOut);
  }
}

void GameState::AppendPlayersInfo(string &info) const {
  for (int i = 0; i < MaxPlayerCount; i++) {
    PlayerList[i]->AppendPlayerInfo(info);
    if (i < MaxPlayerCount - 1)
      info += ", ";
  }
  info += " | Current Player = P" + to_string(currPlayerNumber);
}

// ========== Available Commands ==========

void GameState::SetAvailableCommands(Command cmds[], int count) {
  availableCommandsCount = count;
  for (int i = 0; i < count; i++)
    availableCommands[i] = cmds[i];
}

void GameState::GenerateAvailableCommands() {
  Player *pPlayer = GetCurrentPlayer();
  if (!pPlayer)
    return;

  int health = pPlayer->GetHealth();
  availableCommandsCount = health;
  if (availableCommandsCount < 5) {
    availableCommandsCount = 5;
  }
  if (availableCommandsCount > MaxAvailableCommands) {
    availableCommandsCount = MaxAvailableCommands;
  }

  // Generate random commands
  for (int i = 0; i < availableCommandsCount; i++) {
    // Generate a random command between 1 and COMMANDS_COUNT - 1
    int randCmd = (rand() % (COMMANDS_COUNT - 1)) + 1;
    availableCommands[i] = (Command)randCmd;
  }
}

Command GameState::GetAvailableCommand(int index) const {
  if (index >= 0 && index < availableCommandsCount)
    return availableCommands[index];
  return NO_COMMAND;
}

int GameState::GetAvailableCommandsCount() const {
  return availableCommandsCount;
}
