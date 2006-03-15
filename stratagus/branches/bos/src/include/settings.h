//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name settings.h - The game settings headerfile. */
//
//      (c) Copyright 2000-2005 by Andreas Arens and Jimmy Salmon
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; only version 2 of the License.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//
//      $Id$

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

//@{

#include <vector>

/*----------------------------------------------------------------------------
--  Declarations
----------------------------------------------------------------------------*/

class CFile;
class CMap;
class CampaignChapter;

/*----------------------------------------------------------------------------
--  Settings  __WIP__
----------------------------------------------------------------------------*/

/**
**  Settings structure
**
**  This structure one day should contain all common game settings,
**  in-game, or pre-start, and the individual (per player) presets.
**  This allows central maintainance, easy (network-)negotiation,
**  simplifies load/save/reinitialization, etc...
**
*/
class Settings {
public:
	int NetGameType;   /// Multiplayer or single player

//  Individual presets:
//  For single-player game only Presets[0] will be used..
	struct {
		int Race;  /// Race of the player
		int Team;  /// Team of player -- NOT SELECTABLE YET
		int Type;  /// Type of player (for network games)
	} Presets[PlayerMax];

//  Common settings:
	int Resources;   /// Preset resource factor
	int NumUnits;    /// Preset # of units
	int Opponents;   /// Preset # of ai-opponents
	int Terrain;     /// Terrain type (summer,winter,...)
	int GameType;    /// Game type (melee, free for all,...)
	bool NoFogOfWar; /// No fog of war
	int RevealMap;   /// Reveal map
};

#define SettingsPresetMapDefault  -1  /// Special: Use map supplied

/**
**  Single or multiplayer settings
*/
#define SettingsSinglePlayerGame  1
#define SettingsMultiPlayerGame   2

/**
**  Resource-Preset factor
*/
#define SettingsResourcesMapDefault  SettingsPresetMapDefault
#define SettingsResourcesLow     0
#define SettingsResourcesMedium  1
#define SettingsResourcesHigh    2

/**
**  NumUnits start settings
*/
#define SettingsNumUnitsMapDefault  SettingsPresetMapDefault
#define SettingsNumUnits1    0

/**
**  GameType settings
*/
enum GameTypes {
	SettingsGameTypeMapDefault = SettingsPresetMapDefault,
	SettingsGameTypeMelee = 0,
	SettingsGameTypeFreeForAll,
	SettingsGameTypeTopVsBottom,
	SettingsGameTypeLeftVsRight,
	SettingsGameTypeManVsMachine,
	SettingsGameTypeManTeamVsMachine,

	// Future game type ideas
#if 0
	SettingsGameTypeOneOnOne,
	SettingsGameTypeCaptureTheFlag,
	SettingsGameTypeGreed,
	SettingsGameTypeSlaughter,
	SettingsGameTypeSuddenDeath,
	SettingsGameTypeTeamMelee,
	SettingsGameTypeTeamCaptureTheFlag,
#endif
};


// ----------------------------------------------------------------------------

#define MAX_BRIEFING_VOICES 20  /// How many intro voices supported
#define MAX_OBJECTIVES 9  /// How many objectives supported

class Intro {
public:
	Intro() : Title(NULL), Background(NULL), TextFile(NULL) {
		memset(VoiceFile, 0, sizeof(VoiceFile));
		memset(Objectives, 0, sizeof(Objectives));
	}

	char *Title;                           /// Intro title
	char *Background;                      /// Background picture
	char *TextFile;                        /// Intro text file
	char *VoiceFile[MAX_BRIEFING_VOICES];  /// Intro voice file
	char *Objectives[MAX_OBJECTIVES];      /// Objectives text
};  /// Intro definition


// ----------------------------------------------------------------------------

extern std::vector<char *> Tips;  /// Array of tips
extern bool ShowTips;             /// Show tips at start of level
extern int CurrentTip;            /// Current tip to display

/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

extern Settings GameSettings;  /// Game settings
extern Intro    GameIntro;     /// Game intro

/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

	/// Show level intro
extern void ShowIntro(const Intro *intro);
	/// Show picture
extern void ShowPicture(CampaignChapter *chapter);
	/// Show stats
extern void ShowStats();
	/// Register CCL functions for objectives
extern void ObjectivesCclRegister(void);
	/// Save the objectives
extern void SaveObjectives(CFile *file);
	/// Create a game
extern void CreateGame(const char *filename, CMap *map);
	/// Init Setting to default values
extern void InitSettings(void);

//@}

#endif // !__SETTINGS_H__
