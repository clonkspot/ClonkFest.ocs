/*-- 
	Pickers
	Author: Pyrit
	
	Another Clonk Fest game.
--*/

#include GameBase

func GetGameAuthor() { return "Pyrit"; }
func GetGameSection() { return "Pickers"; }
func GetGameClonkMaxContents() { return 0; }

func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-61)+30, y=188}; }

local MySproutberry, trees;
local GoalNumBerries = 20;

func InitGame(array players)
{
	// Init definitions
	MySproutberry = { Prototype=Sproutberry, Entrance=this.Sproutberry_Entrance };
	//Smooth ground!
	DigFreeRect(0, 195, LandscapeWidth(), 6);
	//Grass!
	for (var i = 0; i < 100; i++)
		CreateObject(Grass, i*5+RandomX(-5,5), 200+RandomX(-1,1)).Plane=RandomX(1, 499);
	//Trees!
	trees = CreateArray(20);
	for (var i = 0; i < 20; i++) trees[i] = CreateObject(Tree_Coniferous, i*20+RandomX(-15, 15), 205);
	// Scoreboard
	Scoreboard->Init([{key = "game", title = Sproutberry, sorted = true, desc = true, default = "0", priority = 100}]);
	//"Player Initializion"
	for(var plr in  players)
	{
		Scoreboard->SetPlayerData(plr, "game", 0);
				
		var lorry = GetCrew(plr)->CreateObject(Lorry,0,0,plr);
		GetCrew(plr)->SetCommand("Grab", lorry);
		UpdateLorryText(lorry);
		
		//Make 1 start berry for every player
		var berry = CreateObject(MySproutberry, RandomX(20, LandscapeWidth()-20), RandomX(150, 170));
		berry.i = 100;
		berry->SetCon(100);
		berry->AddTimer("StartWobble", RandomX(50, 100));
	}
	Schedule(this, "Frame1()", 1, 0);
	Schedule(this, "Frame15()", 15, 3);
	return;
}

func StartGame(array players)
{
	AddTimer(this.MakeBerry, 6);
	return true;
}

func Sproutberry_Entrance(lorry)
{
	if (g_game) g_game->~OnSproutberryCollection(this, lorry);
	return true;
}

func Frame1()
{
	//This makes adjustments to the vegetation placement
	for(var tree in FindObjects(Find_ID(Tree_Coniferous)))
	{
		tree -> SetClrModulation(HSL(RandomX(25, 50),255,RandomX(180, 255)));
		tree -> SetR(RandomX(-7,7));
		tree -> SetPosition(tree->GetX(),tree->GetY()-8);
		if(!Random(2))
			tree.Plane = RandomX (-20,-1);
		else
			tree.Plane = RandomX(1, 20);
		if(!Random(3)) tree -> CreateObject(MySproutberry, RandomX(-30, 30), RandomX(-40, 0));
	}
	DigFreeRect(0, 195, LandscapeWidth(), 6);
}

func Frame15()
{
	DigFreeRect(0, 195, LandscapeWidth(), 6);
}

func OnSproutberryCollection(object berry, object lorry)
{
	if (!lorry) return;
	if (lorry->GetID() != Lorry) return;
	UpdateLorryText(lorry);
	if (lorry->ContentsCount() >= GoalNumBerries) FinishGame();
}

func UpdateLorryText(object lorry)
{
	var plr = lorry->GetOwner();
	if (plr != NO_OWNER)
	{
		var clr = GetPlayerColor(plr);
		var score = lorry->ContentsCount();
		lorry->Message(Format("@<c %x><c %x>%d/%d</c> {{Sproutberry}}", 0xb4ffffff, (clr&0xffffff)|0xb4000000, score, GoalNumBerries));
		Scoreboard->SetPlayerData(plr, "game", score);
	}
	return true;
}

func OnGameFinished()
{
	//Remove all timers from the berries and stop them from falling
	for(var berry in FindObjects(Find_ID(Sproutberry)))
	{
		berry->SetAction("Float");
		berry->SetYDir(0);
		berry->RemoveTimer("Grow");
		berry->RemoveTimer("StartWobble");
		berry->RemoveTimer("Wobble");
		berry->RemoveTimer("LimitSpeed");
	}
	//Trees don't grow new berries
	RemoveTimer("MakeBerry");
	// Determine winner(s)
	var winners = [];
	for (var plr in GetGamePlayers())
	{
		var lorry = FindObject(Find_ID(Lorry), Find_Owner(plr));
		if (lorry && lorry->ContentsCount()>=GoalNumBerries) winners[GetLength(winners)] = plr;
	}
	SetGameWinners(winners, true);
	// Schedule end sequence
	ScheduleCall(this, this.EndSequence, 25, 10, winners);	//Let the winners do some eating animation...
	return 125; // end in 125 frames
}

func MakeBerry()
{
	var n = GetLength(trees);
	var tree = trees[Random(n)];
	if(ObjectCount(Find_OCF(OCF_NotContained),Find_ID(Sproutberry))<=10*GetPlayerCount())
	{
		if(!Random(3))
		{
		if(!Random(2))
			CreateObject(MySproutberry, tree->GetX()+RandomX(-30, 30), tree->GetY()+RandomX(-30, 0));
		else
			CreateObject(MySproutberry, tree->GetX()+RandomX(-15, 15), tree->GetY()+RandomX(-55, -30));
		}
	}
}

func EndSequence(array winners)
{
	for (var plr in winners)
	{
		var clonk = GetCrew(plr);
		if (clonk)
		{
			clonk->SetAction("Eat");
			clonk->Sound("Munch1");
			ScheduleCall(this, this.EndSequenceJuice, 9, 1, clonk);	//Juice with delay...
		}
	}
}

func EndSequenceJuice(object clonk)
{
	if (clonk)
	{
		var particle = Particles_Colored(Particles_Spark(), 0xff00ff);
		clonk->CreateParticleAtBone("MagicSpark", "skeleton_head", [0, -3, 0], [RandomX(-10, 10), RandomX(-10, 10), RandomX(-10, 10)], 36, particle, 15);
	}
}




local Name = "$Name$";
local Description = "$Description$";
