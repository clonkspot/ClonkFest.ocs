/*
	Balloon
	Author: Sven2

	Floats up and waits to be destroyed.
*/

local pop_cb; // callback object when balloon is popped
local score; // score to pass to callback object

protected func Initialize()
{
	// make this.ActMap.Float.Speed modifyable at runtime
	this.ActMap = { Prototype = GetID().ActMap };
	this.ActMap.Float = { Prototype = GetID().ActMap.Float };
	SetAction("Float");
	SetPhase(Random(3));
	SetComDir(COMD_Up);
	AddTimer(this.Timer, 4);
	SetClrModulation(HSL(Random(256), 200+Random(55), 100+Random(120)));
	//SetDir(Random(2)); - looks weird cuz of shading
	return 1;
}

func Init(object callback_obj, int type, def overlay_gfx, int score, int size, int speed)
{
	SetCon(size);
	SetPhase(type);
	SetGraphics(nil, overlay_gfx, 1, GFXOV_MODE_IngamePicture);
	if (overlay_gfx)
	{
		SetObjDrawTransform(500,200,-1000,  -200,500,-17000 * size/100, 1);
		SetClrModulation(0xa0ffffff, 1);
	}
	pop_cb = callback_obj;
	this.score = score;
	if (speed) this.Action.Speed = speed;
	return true;
}

func CatchBlow(int dmg, object projectile)
{
	if (!projectile) return;
	var dy = (projectile->GetY() - GetY()) * 100 / GetCon();
	if (dy < 13)
	{
		Sound("Objects::Balloon::Pop");
		if (pop_cb) pop_cb->OnBalloonPopped(score, projectile->GetController());
		projectile->~Hit();
		RemoveObject();
	}
	return true;
}

func Timer()
{
	SetXDir(GetWind());
	if (GetY() < -GetDefHeight()) return RemoveObject();
}

local ActMap = {

Float = {
	Prototype = Action,
	Name = "Float",
	Procedure = DFA_FLOAT,
	Speed = 200,
	Accel = 100,
	Decel = 16,
	Directions = 1,
	FlipDir = 1,
	Length = 3,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 50,
	Hgt = 75,
	NextAction = "Float",
},
};
local Name = "$Name$";
local Description = "$Description$";
local Plane = -1; // default behind landscape
