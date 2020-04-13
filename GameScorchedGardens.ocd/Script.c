/*-- 
	Scorched Gardens
	Author: Luchs / Mimmo_O
	
	A melee in a fiery setting.
--*/

#include GameBase

/* Overloads by games */

// Your name here
func GetGameAuthor() { return "Luchs / Mimmo_O"; }

// Section of landscape to be used for this game
// Multiple games may share the same map and a map may have multiple maps.
func GetGameSection() { return "ScorchedGardens"; }

// Callback function to be overloaded for custom game initialization
// This is called after section load and all generic game initialization (Clonk placement, player properties set, etc.)
// players is an array of player numbers of players that participate. Do not assume that all players take part.
func InitGame(array players)
{
	// Enviroment.
	CreateObject(Rule_ObjectFade)->DoFadeTime(10 * 36);
	SetSkyAdjust(RGB(255, 128, 0));
	SetSkyParallax(1, 20, 20, 0, 0, nil, nil);
	CreateObjectAbove(Column, 160, 304)->SetClrModulation(RGB(255, 100, 80));
	CreateObjectAbove(Column, 448, 272)->SetClrModulation(RGB(255, 100, 80));
	SetMatAdjust(RGB(255, 150, 128));
	
	CreateEffect(this.RandomMeteor, 100, 20);
	CreateEffect(this.DangerousLava, 100, 1);

	PlaceEdges();
	PlaceGras();

	for (var plr in players)
	{
		var clonk = GetCrew(plr);
		clonk->CreateParticle("Fire", 0, 0, PV_Random(-20, 20), PV_Random(-40, 5), PV_Random(20, 90), Particles_Glimmer(), 30);
		clonk->SetYDir(-5);
		clonk->CreateContents(TeleGlove);
	}

	return true;
}

local DangerousLava = new Effect
{
	Timer = func()
	{
		for (var burning in FindObjects(Find_ID(Clonk),Find_OCF(OCF_OnFire)))
			burning->DoEnergy(-3); 
	},
};

local RandomMeteor = new Effect
{
	Timer = func()
	{
		if (!Random(GetPlayerCount() + 2)) 
			return FX_OK;
		var meteor = LaunchMeteor(50 + Random(LandscapeWidth() - 100), -10, 40 + Random(40), RandomX(-20, 20), 0);
		meteor->DoCon(100);
		RemoveEffect("IntMeteor", meteor);
		meteor->CreateEffect(this.Meteor, 100, 1);
	},

	Meteor = new Effect
	{
		Start = func()
		{
			this.smoketrail = 
			{
				R = 255,
				B = PV_KeyFrames(0,  0,100,    30,0,  100,255, 1000,255),
				G = PV_KeyFrames(0,  0,150,  30,0, 100,255, 1000,255),

				Alpha = PV_KeyFrames(1000, 0, 0, 30, 255, 1000, 0),
				Size = PV_Linear(10,30),
				Stretch = 1000,
				Phase = PV_Random(0,4),
				Rotation = PV_Random(-Target->GetR() - 15, -Target->GetR() + 15),
				DampingX = 1000,
				DampingY = 1000,
				BlitMode = 0,
				CollisionVertex = 0,
				OnCollision = PC_Stop(),
				Attach = nil
			};
			this.brighttrail = new this.smoketrail
			{
				Alpha = PV_Linear(180,0),
					  Size = PV_Linear(20,30),
					  BlitMode = GFX_BLIT_Additive,
			};
			this.frontburn = 
			{
				R = 255,
				B = 50,
				G = 190,

				Alpha = PV_KeyFrames(0, 0, 0, 500, 25, 1000, 0),
				Size = PV_Linear(4,5),
				Stretch = 1000,
				Phase = PV_Random(0,4),
				Rotation = PV_Random(-Target->GetR() - 15, -Target->GetR() + 15),
				DampingX = 800,
				DampingY = 800,
				BlitMode = GFX_BLIT_Additive,
				CollisionVertex = 0,
				OnCollision = PC_Stop(),
				Attach = ATTACH_Front | ATTACH_MoveRelative,
				ForceX = PV_Random(-10, 10, 10),
				ForceY = PV_Random(-10, 10, 10),
			};
		},

		Timer = func()
		{
			var size = Target->GetCon();
			// Air drag.
			var ydir = Target->GetYDir(100);
			ydir -= size * ydir ** 2 / 11552000; // Magic number.
			Target->SetYDir(ydir, 100);
			// Smoke trail.
			Target->CreateParticle("SmokeThick", PV_Random(-5, 5), PV_Random(-5, 5), PV_Random(-3, 3), PV_Random(-3, 3), 20, this.smoketrail, 5);
			// Flash
			Target->CreateParticle("SmokeThick", PV_Random(-2, 2), PV_Random(-2, 2), PV_Random(-3, 3), PV_Random(-3, 3), 3, this.brighttrail, 2);
			// left and right burn
			Target->CreateParticle("FireDense", PV_Random(-5, 5), PV_Random(-5, 5), PV_Random(-20, 20), PV_Random(-20, 20), 40, this.frontburn, 20);
		},
	},
};

private func PlaceEdges()
{
	var x = [69, 69, 76, 84, 484, 76, 565, 565, 532, 68, 68, 476, 468, 532];
	var y = [357, 349, 364, 364, 260, 300, 305, 313, 313, 300, 308, 260, 268, 305];
	var d = [2, 3, 2, 1, 0, 0, 3, 2, 1, 3, 2, 3, 3, 0];
	for (var i = 0; i < GetLength(x); i++)
		DrawMaterialTriangle("Brick-brick", x[i], y[i], d[i]);
	return;
}

private func PlaceGras()
{
	var x=[502,468,530,525,548,560,555,551,461,483,354,425,348,343,338,420,412,405,300,315,310,305,290,193,198,169,181,176,127,137,142,133,122,147,35,45,41,30,122];
	var y=[225,221,201,206,191,178,181,185,228,220,190,234,190,188,188,231,226,221,229,218,221,228,229,262,260,261,261,259,227,227,230,228,237,240,221,221,219,222,224];
	var r=[45,-45,-45,-45,-45,-45,-45,-45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-45,45,45,0,-45,0,-45,45,0,-45,90];
	for (var i = 0; i < GetLength(x); i++)
	{
		while(GBackSolid(x[i],y[i])) y[i]--;
		var edge=CreateObjectAbove(Grass, x[i], y[i] + 5, NO_OWNER);
		edge->SetCategory(C4D_StaticBack);
		edge->SetR(r[i]); 
		edge->Initialize();
		edge->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
		
	}
	return;
}

// Callback function when game is finished
// Call stuff like SetGameWinners() here.
func OnGameFinished()
{
	// By default, all players that aren't ghosts win the game
	SetGameWinners(GetLivingGamePlayers());
	return true;
}

/* Optional overloads */

// Player Clonk start position. Called once for each player. Called again for ghosts if there is no crew object left
func GetGameStartPos(int player, int start_index, int max_index)
{
	var pos = { x = RandomX(75, 500), y = 100 };
	while (!GBackSolid(pos.x, pos.y)) pos.y += 1;
	pos.y -= 30;
	return pos;
}

// Max energy of Clonks
func GetGameClonkMaxEnergy() { return 50; }

// Only a teleglove!
func GetGameClonkMaxContents() { return 1; }

// Return true if game should end automatically if only one player is left alive
func IsGameLastManStanding() { return true; }

/* Basic information - set localizaed name and description in string tables */

local Name = "$Name$";
local Description = "$Description$";
