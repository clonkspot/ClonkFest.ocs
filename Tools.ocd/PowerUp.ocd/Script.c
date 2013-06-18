/**
	PowerUp
	Beschreibung hier einf�gen

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

func ReturnValue()
{
	return(250);
}

public func OnProjectileHit(object shot)
{
	if (shot->GetID()==Arrow)
	{
	CreateParticle("Blast", 0,0, 0,0, 150);
	CastParticles("Spark",30,30,0,0,15,30,RGB(255,255,150),RGB(255,255,200));
	Sound("BalloonPop", false, 1);
	var shooter = shot -> GetController();
	DoWealth(shooter, ReturnValue());
	var msg = CreateObject(FloatingMessage);
	msg->SetMessage(Format("1UP!!!|+%d</c>!", ReturnValue()));
	var rgba = SplitRGBaValue(GetPlayerColor(shooter));
	msg->SetColor(rgba[0], rgba[1], rgba[2], rgba[3]);
	msg->FadeOut(1, 10);
	msg->SetSpeed(0, -5);
	FindSpot();
	RemoveObject();
	}
}

func FindSpot()
{
	var tries;
	var X = Random(LandscapeWidth());
	while(GBackSolid(X-GetX(), HorizonHeight()-5-GetY()) && tries < 20)
	{
		var X = Random(LandscapeWidth());
		tries++;
		//Log("Looking for spot without brick! At X level %d", X);
	}
	if(!GBackSolid(-GetX()+X, HorizonHeight()-5-GetY()))
	CreateBrick(X);
	else
	{
		var damagedBrick = FindObjects(Find_ID(EarthBrick), Sort_Reverse(Sort_Func("GetDamage")))[0];
		damagedBrick -> DoDamage(-damagedBrick->GetDamage());
		//damagedBrick -> SetClrModulation(RGBa(0, 255, 0, 255));
		DrawParticleLine("StarSpark",-GetX()+damagedBrick->GetX(), -GetY()+damagedBrick->GetY(), 0, 0, 5, 25, 0, 0, 0);
		damagedBrick->Sound("GateHit");
		Log("Healing some brick");
	}
	
}

func CreateBrick(int X)
{	
	Log("Creating brick at X %d!", X);
	var brickX = 10;
	while(X>=brickX)
	{
		brickX += 20;	
	}
	var newBrick = CreateObject(EarthBrick, -GetX()+brickX, -GetY()+HorizonHeight());
	DrawParticleLine("StarSpark",-GetX()+newBrick->GetX(), -GetY()+newBrick->GetY(), 0, 0, 5, 25, 0, 0, 0);
	//newBrick->SetClrModulation(RGBa(0, 0, 255, 255));
	newBrick->Sound("GateHit");
}