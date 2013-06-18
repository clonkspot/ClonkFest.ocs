/*--- Rock ---*/

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
	}
};
func Initialize()
{
	AddEffect("HitCheck", this, 1,2, nil,nil);
	SetAction("Float");
	SetComDir(COMD_None);
	SetObjectBlitMode(GFX_BLIT_Additive);
}

func Launch(int targetX, int targetY)
{
		var ang = Angle(GetX(), GetY(), targetX, targetY);
		SetVelocity(ang, 15);
}

protected func Construction()
{
	var graphic = Random(10);
	if(graphic)
		SetGraphics(Format("%d",graphic));
}

public func HitObject(object obj)
{	
	if(obj->GetID()==Clonk)
	{
	ProjectileHit(obj,0,ProjectileHit_tumble);
	obj->SetYDir(-10);
	obj->SetXDir(GetXDir());
	obj->Hurt();
	RemoveEffect("HitCheck", this);
	AddEffect("Cooldown", this, 20, 10);
	}
}

func FxCooldownTimer(target, effect, effect_time)
{
	if(effect_time > 3) 
	{
		AddEffect("HitCheck", this, 1,2, nil,nil);
		return -1;
	}
}

func RejectCollect()
{
	return true;
}

local Name = "$Name$";
local Description = "$Description$";
local Rebuy = true;
