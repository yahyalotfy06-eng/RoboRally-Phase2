#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode
	SET_FLAG_CELL,	// Set Flag on a Cell
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode
	NEW_GAME,
	///TODO: Add more action types of Design Mode

	ADD_ANTENNA,		//start of added items
	ADD_BELT,
	ADD_WATER_PIT,
	ADD_DANGER_ZONE,
	ADD_WORKSHOP,
	ADD_ROTATING_GEAR,
	COPY_NODE,
	CUT_NODE,
	PASTE_NODE,
	DELETE_NODE,
	SAVE_GRID,
	LOAD_GRID,			//end of added items


	//  [2] Actions of Play Mode

	EXECUTE_COMMANDS,	// Execute the saved commands
	SELECT_COMMAND,		// Select a command from the available ones to be executed

	TO_DESIGN_MODE,	// Go to Design Mode

	///TODO: Add more action types of Play Mode
	REBOOT_REPAIR, //start of added items
	USE_TOOLKIT_ACTION,
	USE_HACK_DEVICE_ACTION,
	USE_EXTENDED_MEMORY,
	USE_DOUBLE_LASER,


	//  [3] Others

	EMPTY,							// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,						// Inside Grid Area
	STATUS 							// Inside StatusBar Area
};

enum Direction // Directions of the game
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum PhaseType // Phases of the game
{
	PHASE_MOVEMENT,
	PHASE_SHOOTING // [OPTIONAL BONUS]
};

enum ConsumableType {
	ITEM_NONE,
	ITEM_EXTENDED_MEMORY,
	ITEM_TOOLKIT,
	ITEM_HACK_DEVICE,
	ITEM_DOUBLE_LASER
};

enum Command
{
	NO_COMMAND,
	MOVE_FORWARD_ONE_STEP,
	MOVE_BACKWARD_ONE_STEP,
	MOVE_FORWARD_TWO_STEPS,
	MOVE_BACKWARD_TWO_STEPS,
	MOVE_FORWARD_THREE_STEPS,
	MOVE_BACKWARD_THREE_STEPS,
	ROTATE_CLOCKWISE,
	ROTATE_COUNTERCLOCKWISE,

	COMMANDS_COUNT,
};

enum GameObjectType {  //shahd
	FLAG_TYPE,
	WATERPIT_TYPE,
	DANGERZONE_TYPE,
	BELT_TYPE,
	WORKSHOP_TYPE,
	ANTENNA_TYPE,
	ROTATINGGEAR_TYPE,
};
#endif