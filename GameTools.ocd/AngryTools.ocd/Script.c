/*--    DeadlyTool    --*/


local rotationArray = [0,1,0];
local isTarget = 1;
local ContactCalls = 1;
local ActMap = {
	Float = {
			Prototype = Action,
			Name = "Float",
			Procedure = DFA_FLOAT,
			Directions = 2,
			Speed = 1000,
			Wdt = 64,
			Hgt = 54,
			NextAction = "Float",
	},
	GotHit = {
			Prototype = Action,
			Name = "GotHit",
			Procedure = nil,
			Directions = 2,
			Speed = 1000,
			Wdt = 64,
			Hgt = 54,
			NextAction = "GotHit",
	},
	None = {
			Prototype = Action,
			Name = "None",
			Procedure = nil,
			Directions = 2,
			Speed = 1000,
			Wdt = 64,
			Hgt = 54,
			NextAction = "None",
	}
};

public func Initialize()
{
    SetAction("Float");
    SetR(180);
    AddEffect("Rotate", this, 1, 1, this);
}

func FxRotateTimer(target, effect, effect_time)
{	
	this["MeshTransformation"] = Trans_Rotate(effect_time*10, this.rotationArray[0], this.rotationArray[1], this.rotationArray[2]);
	//Log("%d", effect_time);
}

protected func ContactBottom()
{
	var hitBrick = FindObject(Find_AtPoint(0,ReturnHeight()/2+1), Find_ID(EarthBrick));
	BlastFree(GetX(),GetY()+ReturnHeight()/2+5,10);
	if(hitBrick) {
	hitBrick->DoDamage(ReturnDamage());
	}
	Collide();
}

public func IsProjectileTarget(target,shooter)
{
	return this.isTarget;
}

func ReturnDamage()
{
	return 60;
}

func ReturnHeight() //Be advised: height should always be an even number, because it gets divided by 2 later...
{
	return GetDefCoreVal("Height", "DefCore");
}

func Collide()
{
	this.isTarget = 0;
	this.rotationArray = [1,0,0];
	SetCategory(C4D_Vehicle);
	SetAction("None");
	SetYDir(-26);
	SetXDir(5*(Random(2)*2-1));
	while(RemoveVertex());
	return true;
}

public func OnProjectileHit(object shot)
{
	if (shot && shot->GetID()==Arrow)
	{
		var xdir = shot->GetXDir()/3, ydir = shot->GetYDir();
		shot->CreateParticle("WoodChip", 0,0, PV_Random(xdir-5,xdir+5), PV_Random(ydir-5,ydir+5), PV_Random(10,50), Particles_Spark(), 5);
		Sound("Objects::Balloon::Pop", false, 1);
		ScheduleCall(shot, RemoveObject, 1);
		// Turn to hit mode
		this.rotationArray = [1,0,0];
		SetCategory(C4D_Vehicle);
		SetAction("GotHit");
		SetYDir(-26);
		SetXDir(xdir);
	}
	return true;
}
