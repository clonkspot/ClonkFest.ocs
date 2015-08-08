/**
	PowerUp
	Beschreibung hier einfügen

	@author <Insert Author>
*/

#include AngryTool

local Name = "$Name$";
local Description = "$Description$";

func Initialize()
{
	inherited(...);
	SetRDir(RandomX(-10,10));
}

func ReturnDamage()
{
	return(0);
}

public func OnProjectileHit(object shot)
{
	if (shot->GetID()==Arrow)
	{
	ExplosionEffect(15, 0, 0);
	CreateParticle("MagicSpark", 0,0, PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Spark(), 30);
	Sound("BalloonPop", false, 1);
	var shooter = shot -> GetController();
	FindSpot();
	RemoveObject();
	}
}

func FindSpot()
{
	var tries;
	var X = Random(LandscapeWidth());
	var HorizonHeight=180;
	if (g_game) HorizonHeight = g_game.HorizonHeight;
	while(GBackSolid(X-GetX(), HorizonHeight-5-GetY()) && tries < 20)
	{
		var X = Random(LandscapeWidth());
		tries++;
		//Log("Looking for spot without brick! At X level %d", X);
	}
	if(!GBackSolid(-GetX()+X, HorizonHeight-5-GetY()))
	CreateBrick(X);
	else
	{
		var damagedBrick = FindObjects(Find_ID(EarthBrick), Sort_Reverse(Sort_Func("GetDamage")))[0];
		damagedBrick -> DoDamage(-damagedBrick->GetDamage());
		//damagedBrick -> SetClrModulation(RGBa(0, 255, 0, 255));
		DrawParticleLine("StarSpark",-GetX()+damagedBrick->GetX(), -GetY()+damagedBrick->GetY(), 0, 0, 5, 25, 0, 0, 0);
		damagedBrick->Sound("GateHit");
		//Log("Healing some brick");
	}
	
}

func CreateBrick(int X)
{	
	var HorizonHeight=180;
	if (g_game) HorizonHeight = g_game.HorizonHeight;
	//Log("Creating brick at X %d!", X);
	var brickX = 10;
	while(X>=brickX)
	{
		brickX += 20;	
	}
	var newBrick = CreateObjectAbove(EarthBrick, -GetX()+brickX, -GetY()+HorizonHeight);
	var particles =
	{
		Prototype = Particles_Air(),
		Size = PV_Linear(4, 0)
	};
	DrawParticleLine("StarSpark",-GetX()+newBrick->GetX(), -GetY()+newBrick->GetY(), 0, 0, 5, 0, 0, 25, particles);
	//newBrick->SetClrModulation(RGBa(0, 0, 255, 255));
	newBrick->Sound("GateHit");
}