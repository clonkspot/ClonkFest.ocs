/*
	Maze mouse
	Author: Sven2

	The protoganist of another game. Witty and nimble if skillfully controlled ;-)
*/

#include Library_HUDAdapter

local last_x, last_y, time;

func Initialize()
{
	MakeInvincible(); // Mice are strong!
	SetAction("Walk");
	last_x = GetX(); last_y = GetY();
	time = 0;
	AddTimer(this.Walking, 2);
	SetComDir(COMD_None);
	SetCon(25); // Mice are small!
	return _inherited(...);
}

func Walking()
{
	var x = GetX(), y = GetY();
	if (x == last_x && y == last_y) return;
	++time;
	if (time % 2) SetPhase(!GetPhase());
	SetR(Angle(last_x, last_y, x, y));
	last_x = x; last_y = y;
	// TODO sound
	return true;
}

func Recruitment(int plr)
{
	SetPlayerControlEnabled(GetOwner(), CON_Aim, true);
	return _inherited(plr, ...);
}

func Destruction()
{
	// assume only one mouse per player just got removed
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
		var d = Distance(x,y);
		if (d > 5)
		{
			var max_speed = ActMap.Walk.Speed / 10;
			SetXDir(x*max_speed/d);
			SetYDir(y*max_speed/d);
		}
		else
		{
			SetXDir(); SetYDir();
		}
		//SetPosition(x+GetX(),y+GetY());
	}
	return true;
}

// Properties
local MaxEnergy = 1337;

local ActMap = {

Walk = {
	Prototype = Action,
	Name = "Walk",
	Procedure = DFA_FLOAT,
	Speed = 200,
	Accel = 0,
	Decel = 0,
	X = 0,
	Y = 0,
	Wdt = 30,
	Hgt = 66,
	Length = 2,
	Delay = 0,
	Directions = 1,
	FlipDir = 1,
	NextAction = "Walk",
},

};
