/*-- 
	Party game: Tron
	Author: Sven2
	
	Another Clonk Fest game.
--*/

#include GameBase

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Tron"; }

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


// Player restrictions. Return nil for no limit.
//func GetGameMinPlayers() { return 2; }
//func GetGameMaxPlayers() { return nil; }

func GetGameMaxZoomRange() { return {x=LandscapeWidth(), y=LandscapeHeight()}; }
func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-100)+50, y=Random(LandscapeHeight()-100)+50}; }

func GetGameClonkType() { return GIDL_Clonk; }

func GetGameClonkMaxContents() { return 0; }
func IsGameLastManStanding() { return true; }

local Name = "$Name$";
local Description = "$Description$";
