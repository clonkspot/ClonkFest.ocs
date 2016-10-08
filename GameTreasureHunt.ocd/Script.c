/*-- 
	Party game: Treasure Hunt
	Author: Sven2
	
	Find the golden treasure!
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "TreasureHunt"; }
func GetGameClonkMaxEnergy() { return 42; }
func GetGameStartPos(int player, int start_index, int max_index) { return {x=LandscapeWidth()/2+Random(100)-50, y=50}; }
func GetGameClonkMaxContents() { return 5; }
func GetGameTimeLimit() { return 300; }

func InitGame(array players)
{
	// Tools!
	for (var plr in players)
	{
		var clonk = GetCrew(plr);
		if (clonk)
		{
			clonk->CreateContents(Shovel);
			clonk->CreateContents(Pickaxe);
			clonk->CreateContents(Dynamite);
			clonk->CreateContents(Dynamite);
			clonk->CreateContents(WallKit);
			clonk.Collection2 = this.Clonk_Collection2;
		}
	}
	// Treasure
	var chests = FindObjects(Find_ID(Chest));
	var n_chests = GetLength(chests);
	if (n_chests) chests[Random(n_chests)]->CreateContents(Treasure);
	// Player deactivation
	return inherited(players, ...);
}

func Clonk_Collection2(object obj)
{
	if (obj->GetID() == Treasure && g_game) g_game->FinishGame();
	Call(Clonk.Collection2, obj, ...);
}

func OnGameFinished()
{
	// Winner: The one who has a treasure
	var winners = [], crew;
	for (var obj in FindObjects(Find_ID(Treasure)))
		if (crew = obj->Contained())
			if (crew->GetOwner() != NO_OWNER)
				winners[GetLength(winners)] = crew->GetOwner();
	if (!GetLength(winners)) return 1; // nobody found it
	SetGameWinners(winners, true);
	ScheduleCall(this, this.EndSequence, 25, 10, winners);	//Effects at winner Clonks
	return 125;
}

func EndSequence(winners)
{
	for (var plr in winners)
	{
		var crew = GetCrew(plr);
		if (crew)
		{
			crew->Sound("Objects::Balloon::Pop");
			crew->CreateParticle("MagicSpark", RandomX(-5,5),RandomX(-15,-10), PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Colored(Particles_Spark(),0xff8000,0xffff00), 15);
		}
	}
	return true;
}
