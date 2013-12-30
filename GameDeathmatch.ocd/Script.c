/*-- 
	Party game: Deathmatch
	Author: Sven2
	
	A simple melee with last man standing
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Deathmatch"; }
func GetGameClonkMaxEnergy() { return 5; }
func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-101)+50, y=LandscapeHeight()/2}; }
func GetGameClonkMaxContents() { return 2; }

func IsGameLastManStanding() { return true; } // Game should end automatically if only one player is left alive

static Game_Deathmatch_WeaponIndex;

func InitFest()
{
	// First game with a random weapon. Following games iterate over weapons so there is some variety.
	Game_Deathmatch_WeaponIndex = Random(3);
	return _inherited(...);
}

func InitGame(array players)
{
	// Weapons!
	var r = (Game_Deathmatch_WeaponIndex++)%3;
	var weapon = [Sword, Bow, Musket][r];
	var ammo = [nil, Arrow, LeadShot][r];
	for (var plr in players)
	{
		var clonk = GetCrew(plr);
		if (clonk)
		{
			clonk->CreateContents(weapon);
			if (ammo)
			{
				ammo = clonk->CreateContents(ammo);
				if (ammo) ammo->SetInfiniteStackCount();
			}
		}
	}
	// Player deactivation
	return inherited(players);
}
