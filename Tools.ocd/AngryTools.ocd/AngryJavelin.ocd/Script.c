/*--    DeadlyTool    --*/


#include AngryTool


func Initialize()
{
	inherited(...);
	SetR(90);
	SetGraphics(nil, Javelin);
	PlayAnimation("Base", 5, Anim_Const(0), Anim_Const(1000));
	AddEffect("HitCheck", this, 1,2, nil,nil);
}

func ContactBottom()
{
	inherited(...);
	CastParticles("Spark",15,10,0,ReturnHeight()/2-1,15,30,RGB(255,255,150),RGB(255,255,200));
    Sound("LightMetalHit?", false, 20);
}


public func HitObject(object obj)
{
	ProjectileHit(obj,25,ProjectileHit_tumble);
	RemoveEffect("HitCheck", this);
	AddEffect("Cooldown", this, 20, 10);
}

func FxCooldownTimer(target, effect, effect_time)
{
	if(effect_time > 3) 
	{
		AddEffect("HitCheck", this, 1,2, nil,nil);
		return -1;
	}
}

public func OnStrike(object obj)
{
	if(obj->GetAlive())
		Sound("ProjectileHitLiving?", false, 50);
}

func ReturnDamage()
{
	return(30);
}

func ReturnValue()
{
	return(50);
}

