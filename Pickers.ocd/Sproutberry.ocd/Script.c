/*-- Sproutberry --*/

local i=0;
local growthRate;
local Plane = 500;
local maxspeed;

local ActMap = {
	Float = {
		Prototype = Action,
		Name = "Float",
		Directions = 0,
		Procedure = DFA_FLOAT,
		Wdt = 8,
		Hgt = 8,
		Speed = 1000000,
		Length = 1,
		Delay = 0,
		NextAction = "Hold",
	},
	Fall = {
		Prototype = Action,
		Name = "Fall",
		Directions = 0,
		Procedure = DFA_FLIGHT,
		Wdt = 8,
		Hgt = 8,
		Speed = 40,
		Length = 1,
		Delay = 0,
		NextAction = "Fall",
	}
};

func ContactBottom()
{
	Sound("Splat");
	for(var j; j<25; j++)
		CreateParticle("Spark",0,0,RandomX(-15,15),RandomX(-5, -17),15,RGB(255,0,255), nil);
	RemoveObject();
}

func Initialize()
{
	if(this.i==0)
	{
		SetCon(1);
		this.i=1;
		this.growthRate=RandomX(1,4);
		AddTimer("Grow", 1);
	}
	SetAction("Float");
	this.maxspeed = RandomX(6, 15);
}

func Grow()
{
	if(this.i%this.growthRate==0)
	DoCon(1);
	if(GetCon()>=100)
	{
		RemoveTimer("Grow");
		AddTimer("StartWobble", RandomX(50, 100));
		return;
	}
	this.i++;
}

func StartWobble()
{
	RemoveTimer("StartWobble");
	AddTimer("Wobble", 1);
	this.i=0;
}

func Wobble()
{
	this["MeshTransformation"] = Trans_Rotate(SetR(Sin(this.i*20, 30)), 1, 1, 0);
	this.i++;
	if(this.i%60==0)
	{
		RemoveTimer("Wobble");
		FallDown();
	}
}

func FallDown()
{
	this.Collectible=1;
	SetAction("Fall");
	AddTimer("LimitSpeed", 1);
	Sound("Fall?");
}

func LimitSpeed()
{	
	if(GetYDir()>=this.maxspeed)
		SetYDir(this.maxspeed);
}

func RejectEntrance(obj)
{
	if(obj->GetID()==Clonk)
		return true;
	else
	{
		if(FindObject(obj->Find_Exclude(), Find_AtPoint(obj->GetX()-GetX(), obj->GetY()-GetY()), Find_ID(Lorry)))
		{
			SetXDir(RandomX(-7,7));
			SetYDir(-this.maxspeed+2);
			return true;	
		}
		else
			return false;
	}
}

func Complete()
{
	if(GetCon()>=50) return true;
	else return false;
}


local Collectible = 0;