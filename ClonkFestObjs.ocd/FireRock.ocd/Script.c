/*--- FireRock ---*/

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
	SetAction("Float");
	SetComDir(COMD_None);
	SetObjectBlitMode(GFX_BLIT_Additive);
}

func Launch(int targetX, int targetY)
{
	AddEffect("HitCheck", this, 1,2, nil,nil);
	var ang = Angle(GetX(), GetY(), targetX, targetY);
	SetVelocity(ang, 15);
	return true;
}

local particle;

func Launch2(int x, int y, int vx, int vy, int clr)
{
	SetPosition(x,y);
	SetXDir(vx); SetYDir(vy);
	// Color trail
	particle = Particles_Colored(Particles_Air(), clr);
	AddTimer(this.Trail, 4);
	// Calculate when object will leave top of landscape to remove
	if (vy < 0) ScheduleCall(this, "RemoveObject", Max(-10*(y+10)/vy,1), 1);
	return true;
}

func Trail()
{
	var xdir = GetXDir(), ydir = GetYDir();
	CreateParticle("Air", RandomX(-2,2), RandomX(-2,2), xdir/-2+RandomX(-2,2), ydir/-2+RandomX(-2,2), PV_Random(20, 40), particle, 1);
	return true;
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
		obj->~OnProjectileHit(this);
		WeaponTumble(obj, this->TumbleStrength());
		obj->SetYDir(-10);
		obj->SetXDir(GetXDir());
		obj->~PlaySoundHurt();
		RemoveEffect("HitCheck", this);
		AddEffect("Cooldown", this, 20, 10);
	}
}

public func TumbleStrength() { return 100; }

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
