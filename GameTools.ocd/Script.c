/*-- 
	Falling tools
	Author: Pyrit
	
	Shoot the tools.
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

local HorizonHeight = 185;

func GetGameAuthor() { return "Pyrit"; }
func GetGameSection() { return "Tools"; }
func GetGameClonkMaxEnergy() { return 50; }
func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-101)+50, y=HorizonHeight-25}; }
func IsGameLastManStanding() { return true; } // Game should end automatically if only one player is left alive
func GetGameClonkMaxContents() { return 2; }

func InitGame(array players)
{
	//Make a brick floor
	for (var i = 0; i < LandscapeWidth(); i+=20)
	 CreateObject(EarthBrick, i+10, HorizonHeight);
					
	//Grass!     
	PlaceGrass(75);
	
	//Clouds!
	Cloud->Place(5);
	SetWind(100);
	
	//Mushrooms
	for (var i = 0; i < 15; i++)
		CreateObject(ColorMushroom, Random(LandscapeWidth()), HorizonHeight-5).Plane = RandomX(399, 500);
	
	//Grass	
	for (var i = 0; i < 100; i++)
		CreateObject(Grass, Random(LandscapeWidth()), HorizonHeight-5).Plane = RandomX(399, 500);
	
	//Trees!   
	for (var i = 0; i < 10; i++)
			CreateObject(Tree_Coniferous, Random(LandscapeWidth()), HorizonHeight-5);

	//Replacement for InitializePlayer()
	for(var plr in players)
	{
		var index = 0, crew;
		while (crew = GetCrew(plr, index))
		{
			AddEffect("ToolsBurn", crew, 1, 0, this); // Fire damage
			crew.QueryCatchBlow = this.Clonk_QueryCatchBlow;
			var bow = CreateObject(Bow,10,1,plr);
			bow.ContactIncinerate = 0;
			bow.ControlUseHolding = this.Bow_ControlUseHolding;
			var arrow = bow -> CreateContents(Arrow);
			arrow->SetInfiniteStackCount();
			bow -> Enter(crew);
			index++;
		}
	}

 //This makes adjustments to the vegetation placement
	for(var tree in FindObjects(Find_ID(Tree_Coniferous)))
	{
		tree -> SetClrModulation(HSL(RandomX(25, 50),255,RandomX(180, 255)));
		tree -> SetR(RandomX(-15,15));
		tree -> SetPosition(tree->GetX(),135);
		tree.Plane = -1;
	}
	for(var grass in FindObjects( Find_ID(Grass)))
	{
		grass -> SetPosition(grass->GetX(),grass->GetY()-3);
		grass.Plane=-1;
		if(Random(2)) grass.Plane=1;
	}
	
	return true;
}

func StartGame(array players)
{
	//Add a timer that runs for ever
	AddTimer(this.CreateTool, 45);
	// Wrap timer
	AddTimer(this.Timer1, 1);
	return true;
}


func Timer1()
{
	// Wrapping borders
	for (var clonk in FindObjects(Find_ID(Clonk)))
	{
		var x = clonk->GetX();
		if (x >= LandscapeWidth()-4)
			clonk->SetPosition(x-LandscapeWidth()+9, clonk->GetY());
		else if (x <= 4)
			clonk->SetPosition(x+LandscapeWidth()-9, clonk->GetY());
	}
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

local effect_time;

func CreateTool()
{
	if(!Random(8)) return;
	effect_time += 45;
	
	// Remove dead arrows
	for (var arrow in FindObjects(Find_NoContainer(), Find_ID(Arrow), Find_Not(Find_OCF(OCF_HitSpeed1))))
		if(!GetEffect("HitCheck",arrow))
			arrow->RemoveObject();

	//Tools get faster with time
	var speed = RandomX(4000+effect_time,12000+effect_time);
	var tool = RandomTool();
	tool->SetYDir(speed, 8000);
	
	var X;
	//Approx every tenth time a PowerUp gets created
	if(!Random(10))
	{
		//Determines wether it spawns left or right
		if(!Random(2))
			X=1;
		else
		{
			X=LandscapeWidth()-1;
			speed = -speed;
		}
		
		var powerUp = CreateObject(PowerUp, X, RandomX(25, 100));
		powerUp-> SetXDir(speed, 8000);
	}
	
	//Creates a lavachunk and flings it up
	if(!Random(5))
	{
		var bomb = CreateObject(LavaChunk, Random(LandscapeWidth()), LandscapeHeight()-1);
		bomb->Fling(RandomX(-3,3), -7);
	}
}

//Returns a random tool
func RandomTool()
{
	if(!Random(5))
	{
		if(!Random(2))
			return CreateObject(AngrySword, SearchX(1), 8);
		else
			return CreateObject(AngryPickaxe, SearchX(5), 8);
	}
	return CreateObject(AngryShovel, SearchX(5), 10);
}

func SearchX(likelyhood)	//Likelyhood is the chance, that X is directly above a clonk. 1 is always, e.g. 5 is every 5th time
{
	var X = Random(LandscapeWidth());
	
	if (!Random(likelyhood))
	{
		var clonk = FindObjects(Sort_Random(), Find_ID(Clonk), Find_Not(Find_Action("Dead")));
		if (clonk[0]) X = clonk[0]->GetX()+RandomX(-2,2);
	}
	else if(!Random(2))
	{	
		//Tools get only created where there's a brick to destroy. Try 50 times to find such a place
		var tries = 0;
		X = Random(LandscapeWidth());
		while (!GBackSolid(X, HorizonHeight-5) && tries < 50)
		{
			X = Random(LandscapeWidth());
			tries++;
		}
	}	
	return X;
}

// Bow
func Bow_ControlUseHolding(object clonk, int x, int y)
{
	// Save new angle
	var angle = Angle(0,0,x,y);
	angle = Normalize(angle,-180);

	if(angle >  160) angle =  160;
	if(angle < -160) angle = -160;
	if(angle <  35 && angle >  -36)
	{
		if(angle<0)
		angle = -35;
		else
		angle = 35;
	}

	clonk->SetAimPosition(angle);
	
	return true;
}

// Clonk can't be hit by arrows
func Clonk_QueryCatchBlow() { return true; }

