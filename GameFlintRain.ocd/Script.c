/*-- 
	Party game: Flint rain
	Author: Sven2
	
	A simple melee with last man standing
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "FlintRain"; }
func GetGameClonkMaxEnergy() { return 42; }
func GetGameStartPos(int player, int start_index, int max_index) { return {x=LandscapeWidth()/2+Random(100)-50, y=300}; }
func GetGameClonkMaxContents() { return 1; }

func IsGameLastManStanding() { return true; } // Game should end automatically if only one player is left alive

func InitGame(array players)
{
	// Weapons!
	for (var plr in players)
	{
		var clonk = GetCrew(plr);
		if (clonk)
		{
			var kit = clonk->CreateContents(WallKit);
			if (kit) kit->SetStackCount(5);
		}
	}
	// Player deactivation
	return inherited(players, ...);
}

func StartGame(array players)
{
	// Start the flint rain!
	AddTimer(this.Timer, 15);
	// Activate players
	return inherited(players, ...);
}

local time;

func Timer()
{
	// Cast meteors
	++time;
	var n_meteors = Random(2 + time / 100);
	for (var i=0; i<n_meteors; ++i)
	{
		var meteor = CreateObjectAbove(Meteor);
		var x = Random(LandscapeWidth());
		var y = -Random(50);
		var size = RandomX(60, 90);
		var xdir = RandomX(-22, 22);
		var ydir = RandomX(28, 36);
		meteor->Launch(x, y, size, xdir, ydir);		
	}
	if (!Random(70))
	{
		var kit = CreateObjectAbove(WallKit, Random(LandscapeWidth()), 0);
		if (kit)
		{
			kit->SetXDir(RandomX(-22, 22));
			kit->SetStackCount(1+Random(5));
		}
	}
	return true;
}
