#ifndef UI_INFO_H
#define UI_INFO_H

#include "CMUgraphicsLib\CMUgraphics.h"

// User Interface information file.
// This file contains info that is needed by Input and Output classes to
// handle the user interface

#define NumHorizontalCells 11
#define NumVerticalCells 5
#define MaxPlayerCount 2
#define MaxAvailableCommands 10
#define MaxSavedCommands 5

enum GUI_MODE		// Graphical user interface mode
{
	MODE_DESIGN,	// Design mode (startup mode)
	MODE_PLAY       // Play mode
};

enum DESIGN_MODE_ITEMS // The items of the Design Mode (you should add more items)
{
	// Note: Items MUST be ordered here as they appear in menu
	// Order matches Output::CreateDesignModeToolBar() drawing order exactly

	ITM_SET_FLAG_CELL,		// position 0  (Flag icon)
	ITM_EXIT,				// position 1  (Exit icon)
	ITM_SWITCH_TO_PLAY_MODE,// position 2  (Play icon)
	ITM_ADD_ANTENNA,		// position 3
	ITM_ADD_BELT,			// position 4
	ITM_ADD_WATER_PIT,		// position 5
	ITM_ADD_DANGER_ZONE,	// position 6
	ITM_ADD_WORKSHOP,		// position 7
	ITM_ADD_ROTATING_GEAR,	// position 8
	ITM_COPY,				// position 9
	ITM_CUT,				// position 10
	ITM_PASTE,				// position 11
	ITM_DELETE,				// position 12
	ITM_SAVE,				// position 13
	ITM_LOAD,				// position 14

	DESIGN_ITM_COUNT	// no. of items ==> This should be the last line in this enum
};

enum PLAY_MODE_ITEMS // The items of the Play Mode (you should add more items)
{
	// Note: Items are ordered here as they appear in menu
	// If you want to change the menu items order, change the order here

	ITM_EXECUTE_COMMANDS,
	ITM_SELECT_COMMAND,
	ITM_SWITCH_TO_DESIGN_MODE,

	ITM_SET_TURN,		//start of added items
	ITM_REBOOT_REPAIR,
	ITM_NEW_GAME,
	ITM_EXIT_PLAY,		//end of added items

	PLAY_ITM_COUNT		// no. of items ==> This should be the last line in this enum
};


__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,			// Window width and height
		wx , wy,				// Window starting coordinates
		ToolBarHeight,			// Tool Bar Height (distance from top of window to bottom line of toolbar)
		CommandsBarHeight,		// Commands Bar Height (distance from bottom of window to bottom line of commands bar)
		StatusBarHeight,		// Status Bar Height
		MenuItemWidth,			// Width of each item in toolbar menu
		CommandItemWidth;		// Width of the saved commands in the commands bar (not the available commands)

	
	int CellHeight;				// Height of 1 CELL
	int CellWidth;				// Width of 1 CELL
	
	color MsgColor;				// Messages color (usually used in statusbar)
	color PlayerInfoColor;		// Players' Info color (used in the toolbar - right-indented)
	color CommandBarTextColor;	// Commands Bar text color

	color CellColor;			// Default Cell color

	color ToolBarColor;			// Toolbar color (toolbar background)
	color StatusBarColor;		// Statusbar color (statusbar background)
	color CommandBarColor;		// Commands Bar background color

	color GridLineColor;		// Color of the Lines separating adjacent cells

	int CellNumFont;			// Font size of cell numbers
	color CellNumColor;			// Cell number color


	color BeltColor;			// Color of the belt
	color FlagColor;			// Color of the flag
	color FlagPoleColor;		// Color of the flag pole (the vertical part of the flag)
	color DangerZoneCellColor;	// Color of the danger zone cells
	color WaterPitsCellColor;	// Color of the water pits cells


	int SpaceBetweenCommandsSlots; // Space between the slots of the saved commands in the commands bar
	int AvailableCommandsXOffset;	// Size of the horizontal space before drawing the available commands
	int AvailableCommandsYOffset;	// Size of the vertical space between the start of the command bar and the cards of available commands
									// will be used in detecting selected command from the user click
	int BeltXOffset;			// Size of the horizontal space before drawing the belt
	int BeltYOffset;			// Size of the vertical space before drawing the belt
	int BeltLineWidth;			// Width of the belt line
	int FlagWidth;				// Width of the flag
	int FlagHeight;				// Height of the flag
	int FlagPoleWidth;			// Width of the flag pole
	int FlagPoleHeight;			// Height of the flag pole

	color PlayerColors[MaxPlayerCount];		// Color of each player

	int CommandItemsCount;		// Number of commands the player can use
	int AvailableCommandsCount;	// Number of available commands the player can select from


} UI ;	// create a global object UI

#endif