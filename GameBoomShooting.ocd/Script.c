/*-- 
	Boompack target shooting
	Author: K-Pone / Luchs
--*/

#include GameBase

/* Overloads by games */

// Your name here
func GetGameAuthor() { return "K-Pone / Luchs"; }

// Section of landscape to be used for this game
// Multiple games may share the same map and a map may have multiple maps.
func GetGameSection() { return "BoomShooting"; }

local scores;
local target_score = 1000;

local giveboompackfx = new Effect
{
	lastpackat = 0,
	
	Timer = func()
	{
		if (Target->GetHandItem() == nil && (this.Time - this.lastpackat) > 100 )
		{
			if (Target->GetAction() == "Walk" || Target->GetAction() == "Jump" || Target->GetAction() == "Hangle" || Target->GetAction() == "Scale")
			{
				if (Target->GetAction() == "Walk") Target->SetAction("Jump");
				var b = Target->CreateContents(Boompack);
				b.fuel = 200;
				b.dirdev = 12;
				b.controllable = true;

				this.lastpackat = this.Time;
			}

		}
		
	}
};

local keepClonksOnBasefx = new Effect
{
	Start = func()
	{
		this.particle =
		{
			R = PV_Random(100,130),
			G = PV_Random(100,130),
			B = PV_Random(200,230),
			Alpha = PV_Linear(255,0),
			Size = PV_Linear(4,3),
		};
	},

	Timer = func()
	{
		for (var i = 0; i < 10; i++)
		{
			CreateParticle("Flash", 2480, PV_Random(2575, 2720), 0, PV_Random(-2,2), 10, this.particle);
		}
		
		for (var clnk in FindObjects(Find_And(Find_ID(Clonk), Find_Or( Find_InRect(2480, 0, LandscapeWidth() - 2480, LandscapeHeight()), Find_InRect(0, 0, 2280, LandscapeHeight())))))
		{
			if (clnk->GetY() < 2600) clnk->SetPosition(2478,2600);
			if (clnk->GetActionTarget() && clnk->GetActionTarget()->GetID() == Boompack)
			{
				clnk->GetActionTarget()->JumpOff(clnk);
			}
			clnk->Fling(-3,1);
		}
	}
};

local balloonspawnfx = new Effect
{
	Timer = func()
	{
		var posx, posy;
		
		posx = RandomX(LandscapeWidth()/4, LandscapeWidth()/4 * 3);
		posy = RandomX(LandscapeHeight()/2, LandscapeHeight());
		
		while(posx > 2270 && posx < 2530 && posy > 2550)
		{
			posx = RandomX(LandscapeWidth()/4, LandscapeWidth()/4 * 3);
			posy = RandomX(LandscapeHeight()/4, LandscapeHeight());
		}
		
		var t = CreateObject(BoomTarget, posx, posy, NO_OWNER);
		t.hit_cb = Target;
	}
};

// Callback function to be overloaded for custom game initialization
// This is called after section load and all generic game initialization (Clonk placement, player properties set, etc.)
// players is an array of player numbers of players that participate. Do not assume that all players take part.
func InitGame(array players)
{
	CreateEffect(keepClonksOnBasefx, 1, 1);
	CreateEffect(balloonspawnfx, 1, 10);

	scores = [];
	Scoreboard->Init([{key = "game", title = GetID(), sorted = true, desc = true, default = "0", priority = 100}]);
	for (var plr in players)
	{
		scores[plr] = 0;
		Scoreboard->SetPlayerData(plr, "game", 0);
		var crew = GetCrew(plr);
		if (crew)
		{
			crew->CreateContents(WindBag);
			crew->MakeInvincible();
			crew->CreateEffect(giveboompackfx, 1, 1);
			crew->SetPosition(LandscapeWidth() / 2, LandscapeHeight() - 110);
			crew.IsProjectileTarget = this.False;
		}
	}
	DisableAllControls(true);
	return true;
}

func StartGame()
{
	EnableAllControls(true);
	return true;
}

func OnTargetHit(int score, int plr)
{
	if (plr<0) return;
	scores[plr] += score;
	Scoreboard->SetPlayerData(plr, "game", scores[plr]);
	var crew = GetCrew(plr);
	if (crew)
	{
		var fm = CreateObjectAbove(FloatingMessage, crew->GetX() - GetX(), crew->GetY() - GetY(), NO_OWNER);
		if (fm)
		{
			var plr_clr = GetPlayerColor(plr);
			fm->SetColor(GetRGBaValue(plr_clr, 1), GetRGBaValue(plr_clr, 2), GetRGBaValue(plr_clr, 3));
			fm->FadeOut(1+Abs(score)/25, 8);
			fm->SetSpeed(0, -4);
			fm->SetMessage(Format("%d</c>", score));
		}
	}
	if (scores[plr] >= target_score) FinishGame();
	return true;
}

// Callback function when game is finished
// Call stuff like SetGameWinners() here.
func OnGameFinished()
{
	// All players that have reached the target score
	var winners = [];
	for (var plr in GetGamePlayers())
		if (scores[plr] >= target_score)
			winners[GetLength(winners)] = plr;
	SetGameWinners(winners, true);
	return true;
}

func False() { return false; }

func InitializeMap(proplist map)
{
	map->Resize(600,350);
	
	map->Draw("Tunnel-Brickback", { Algo = MAPALGO_Rect, X = 285, Y = 320, Wdt = 24,  Hgt = 20 } );
	
	map->Draw("Brick", { Algo = MAPALGO_Rect, X = 285, Y = 340, Wdt = 30, Hgt = 10 } );
	map->Draw("Brick", { Algo = MAPALGO_Rect, X = 285, Y = 320, Wdt = 26, Hgt = 2 } );
	map->Draw("Brick", { Algo = MAPALGO_Rect, X = 285, Y = 320, Wdt = 2,  Hgt = 20 } );
	
	return true;
}

/* Basic information - set localizaed name and description in string tables */

local Name = "$Name$";
local Description = "$Description$";
