/*-- 
	Party game: Tron
	Author: Sven2
	
	Another Clonk Fest game.
--*/

#include GameBase

/* Overloads by games */

// Your name here
func GetGameAuthor() { return "Sven2"; }

// Section of landscape to be used for this game
// Multiple games may share the same map and a map may have multiple maps.
func GetGameSection() { return "Tron"; }

// Callback function to be overloaded for custom game initialization
// This is called after section load and all generic game initialization (Clonk placement, player properties set, etc.)
// players is an array of player numbers of players that participate. Do not assume that all players take part.
func InitGame(array players)
{
	for (var plr in players)
	{
		var c = GetCrew(plr);
		var launch_con;
		if (!Random(2))
			if (c->GetX() < LandscapeWidth()) launch_con = CON_Right; else launch_con = CON_Left;
		else
			if (c->GetY() < LandscapeHeight()) launch_con = CON_Down; else launch_con = CON_Up;
		c->PreLaunchDrawing(launch_con);
	}
	return true;
}

func StartGame(array players)
{
	for (var plr in players)
	{
		var c = GetCrew(plr);
		c->LaunchDrawing();
	}
	return true;
}

// Callback function when game is finished
// Call stuff like SetGameWinners() here.
func OnGameFinished()
{
	// By default, all players that aren't ghosts win the game
	SetGameWinners(GetLivingGamePlayers());
	return true;
}

// Helper functions:
// GetGamePlayers() - return array of player numbers of players who play in the game
// GetLivingGamePlayers() - return array of players that aren't ghosts
// GhostPlayer(int player) - remove crew of player and turn cursor into a ghost

// SetGameWinners(array winners) - store winners of this game
// FinishGame() - mark game as ended and start next


/* Optional overloads */

// Player restrictions. Return nil for no limit.
//func GetGameMinPlayers() { return 2; }
//func GetGameMaxPlayers() { return nil; }

// Max player zoom range. Set as value and max value at start of game
func GetGameMaxZoomRange() { return {x=LandscapeWidth(), y=LandscapeHeight()}; }

// Player Clonk start position. Called once for each player. Called again for ghosts if there is no crew object left
func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-100)+50, y=Random(LandscapeHeight()-100)+50}; }

// Return true if the player may not scroll around
//func GetGameViewLock() { return true; }

// Default Clonk type. Return nil if no Clonks should be created.
func GetGameClonkType() { return GIDL_Clonk; }

// Max energy of Clonks
//func GetGameClonkMaxEnergy() { return 10; }

// Set this to number of frames if the game should end automatically after a set time
//func GetGameTimeLimit() { return nil; }

// Return true if game should end automatically if only one player is left alive
func IsGameLastManStanding() { return true; }

// Static (definition) call done once a party has been started. Use to init static variables.
//func InitFest() { return true; }


/* Basic information - set localizaed name and description in string tables */

local Name = "$Name$";
local Description = "$Description$";
