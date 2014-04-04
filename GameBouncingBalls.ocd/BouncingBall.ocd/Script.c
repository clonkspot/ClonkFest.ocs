/*
	Bouncing Ball
	Author: Sven2

	The protoganist of another game. Witty and nimble if skillfully controlled ;-)
*/

#include Library_HUDAdapter

local target_x, target_y, is_crew;

func Initialize()
{
	SetAction("Float");
	AddTimer(this.Timer, 1);
	target_x = GetX();
	target_y = GetY();
	SetComDir(COMD_None);
	//if (GetOwner() == -1) SetColor(0xffff0000);
	return _inherited(...);
}

protected func OnEnergyChange()	
{
	var e = GetEnergy(), gfx; //  0      1    2     3     4     5     6     7     8     9    10
	if (Inside(e, 0, 9)) gfx = ["D6", "D6", "D5", "D4", "D3", "D3", "D2", "D2", "D1", "D1", nil][e];
	SetGraphics(gfx);
	return _inherited(...);
}

func Timer()
{
	var x = GetX(), y = GetY();
	var d = Distance(x,y,target_x,target_y);
	var vx = GetXDir(), vy = GetYDir();
	var bounced = 0;
	// collide with landscape borders
	if ((x < 26 && vx < 0) || (x >= LandscapeWidth()-26 && vx > 0))
	{
		vx = -vx;
		bounced = Abs(vx);
	}
	if ((y < 26 && vy < 0) || (y >= LandscapeHeight()-26 && vy > 0))
	{
		vy = -vy;
		bounced = Max(bounced, Abs(vy));
	}
	// enemy collisions
	var coll;
	for (coll in FindObjects(Find_ID(FireRock), Find_AtRect(-16,-16,32,32)))
		if (ObjectDistance(coll) < 20)
		{
			coll->SetObjectLayer(coll);
			Sound("Blast1");
			Global->ExplosionEffect(5, coll->GetX(), coll->GetY());
			coll->RemoveObject();
			DoEnergy(-1);
			if (!this || !GetAlive()) return;
		}
	// other bouncing ball collisions
	for (coll in FindObjects(Find_ID(BouncingBall), Find_AtRect(-16,-16,32,32), Find_Exclude(this)))
		if (ObjectDistance(coll) < 32)
		{
			// Collision! Calculate amount of speed transferred
			var v2x = coll->GetXDir(), v2y = coll->GetYDir();
			var dx = x - coll->GetX(), dy = y - coll->GetY();
			var dvx = v2x-vx, dvy = v2y-vy;
			var tv = dx*dvx+dy*dvy;
			if (tv < 0) continue;
			var tvl = dx*dx+dy*dy;
			if (!tvl) continue;
			var tvx = tv*dx/tvl, tvy = tv*dy/tvl;
			// Transfer speed
			vx += tvx; vy += tvy;
			coll->SetXDir(v2x - tvx);
			coll->SetYDir(v2y - tvy);
			bounced = Max(bounced, tv/Sqrt(tvl));
		}
	if (bounced > 5)
	{
		// TODO sound
		Sound("Click");
	}
	// passive movement
	if (!is_crew) { SetXDir(vx); SetYDir(vy); return true; }
	// active movement: move to target
	var tvx, tvy; // desired speed
	if (d>10)
	{
		// move towards cursor
		tvx = target_x - x;
		tvy = target_y - y;
		DrawParticleLine("Flash", 0,0,tvx,tvy, BoundBy(d/10, 3, 20), 0, 0, 2, Particles_Colored(Particles_Magic(), GetPlayerColor(GetController())));
	}
	else
	{
		// halt
		tvx = tvy = 0;
	}
	//accelerate towards desired speed
	var max_accel = 2;
	SetXDir(BoundBy(tvx, vx-max_accel, vx+max_accel));
	SetYDir(BoundBy(tvy, vy-max_accel, vy+max_accel));
	return true;
}

func Recruitment(int plr)
{
	is_crew = true;
	GameCallEx("OnClonkRecruitment", this, plr);
	SetClrModulation(0xff000000 | GetPlayerColor(plr));
	SetPlayerControlEnabled(GetOwner(), CON_Aim, true);
	return _inherited(plr, ...);
}

func Destruction()
{
	// assume only one ball per player, which just got removed
	SetPlayerControlEnabled(GetOwner(), CON_Aim, false);
	return _inherited(...);
}

// Player pressed da button.
func ObjectControl(int plr, int ctrl, int x, int y, int strength, bool repeat, bool release)
{
	// only controlled by mouse
	if (ctrl == CON_Aim)
	{
		// move towards mouse
		target_x = GetX() + x;
		target_y = GetY() + y;
	}
	return true;
}

// Properties
local MaxEnergy = 10;

local ActMap = {

Float = {
	Prototype = Action,
	Name = "Float",
	Procedure = DFA_FLOAT,
	Speed = 10000,
	Accel = 0,
	Decel = 0,
	FacetBase = 1,
	NextAction = "Float",
},

};
