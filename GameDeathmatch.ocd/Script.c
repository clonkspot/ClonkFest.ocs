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
func GetGameStartPos(int player, int start_index, int player_count)
{
	// Evenly distributed start positions
	var x = 50 + start_index * (LandscapeWidth()-101) / Max(1, player_count-1);
	var y = LandscapeHeight()/2;
	while (!GBackSolid(x, y)) ++y;
	return {x=x, y=y};
}

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
	var weapon = [Sword, Bow, Blunderbuss][r];
	var ammo = [nil, Arrow, LeadBullet][r];
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
