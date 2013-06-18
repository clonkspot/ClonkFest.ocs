/*--    DeadlyTool    --*/


local rotationArray = [0,1,0];
local isTarget = 1;
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
	var speed = GetYDir(1000);
	this.isTarget = 0;
	this.rotationArray = [1,0,0];
	SetCategory(C4D_Vehicle);
	SetAction("None");
	SetYDir(-speed*2, 1000);
	SetXDir(500*LeftOrRight(),1000);
	while(RemoveVertex());
}

public func OnProjectileHit(object shot)
{
	if (shot->GetID()==Arrow)
	{
	CreateParticle("Blast", 0,0, 0,0, 150);
	Sound("BalloonPop", false, 1);
	var shooter = shot -> GetController();
	DoWealth(shooter, ReturnValue());
	var msg = CreateObject(FloatingMessage);
	msg->SetMessage(Format("+%d</c>", ReturnValue()));
	var rgba = SplitRGBaValue(GetPlayerColor(shooter));
	msg->SetColor(rgba[0], rgba[1], rgba[2], rgba[3]);
	msg->FadeOut(1, 20);
	msg->SetSpeed(0, -10);
	if(GetWealth(shooter) > GetPlrExtraData(shooter, "AngryShovelsHighScore"))
	{
		SetPlrExtraData(shooter, "AngryShovelsHighScore", GetWealth());
		Message("@NEW HIGHSCORE!!!");
	}
	RemoveObject();
	}
}

func LeftOrRight()
{
	if(Random(2)) return 2; else return -1;
}

func ReturnValue()
{
	return (10);
}

