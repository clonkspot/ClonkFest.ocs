/*
	GIDL-Clonk
	Author: Sven2

	The protoganist of another game. Witty and nimble if skillfully controlled ;-)
*/

// Last position during Draw action.
// Used to draw tail
local last_x, last_y;

// GIDLClonk cannot be killed by normal means
func Initialize()
{
	MakeInvincible();
}

// Callback at game initialization: Show launch direction and wait
func PreLaunchDrawing(int con_dir)
{
	SetAction("WaitDraw");
	ObjectControl(GetOwner(), con_dir, 0,0, 100);
	return true;
}

// Start movement
func LaunchDrawing()
{
	last_x = GetX(); last_y = GetY();
	SetAction("Draw");
	return true;
}

// Timer during movement: Draw tail
func Drawing()
{
	var x=GetX(), y=GetY();
	var vx=x-last_x, vy=y-last_y;
	last_x = x; last_y = y;
	var v=Distance(vx,vy);
	if (!v) return;
	var s1=v;
	var s2=4;
	var dx1=vx*s1/v, dy1=vy*s1/v, dx2=vy*s2/v, dy2=-vx*s2/v;
	x -= dx1; y -= dy1;
	DrawMaterialQuad("Gold-gold", x+dx1+dx2,y+dy1+dy2, x+dx1-dx2,y+dy1-dy2, x-dx1-dx2,y-dy1-dy2, x-dx1+dx2,y-dy1+dy2, true);
	CreateParticle("MagicSpark", 0,0, PV_Random(-vx*2-15,-vx*2+15), PV_Random(-vy*2-15,-vy*2+15), PV_Random(30,80), Particles_Colored(Particles_Spark(),GetPlayerColor(GetOwner())), 3);
	return true;
}

// Player pressed da button.
func ObjectControl(int plr, int ctrl, int x, int y, int strength, bool repeat, bool release)
{
	if (release) return true;
	var xdir=0, ydir=0, comd;
	if (ctrl == CON_Up)
		{ ydir = -1; comd = COMD_Up; }
	else if (ctrl == CON_Down)
		{ ydir = +1; comd = COMD_Down; }
	else if (ctrl == CON_Left)
		{ xdir = -1; comd = COMD_Left; }
	else if (ctrl == CON_Right)
		{ xdir = +1; comd = COMD_Right; }
	else
		return true; // block anything else
	var is_drawing = (GetAction() == "Draw");
	// No direct turnaround
	if (is_drawing && xdir * GetXDir() + ydir * GetYDir() < 0) { Sound("GIDLTurnError", true, 100, plr); return true; }
	Sound("GIDLTurn");
	var speed = ActMap.Draw.Speed / 10;
	if (is_drawing) Drawing();
	SetComDir(comd);
	if (is_drawing) { SetXDir(xdir*speed); SetYDir(ydir*speed); }
	SetR(Angle(0,0,xdir, ydir));
	return true;
}

// Hitting the wall? The end.
func Hit()
{
	Kill();
	Explode(40);
	return true;
}

// Properties
local MaxEnergy = 1337;

local ActMap = {

Draw = {
	Prototype = Action,
	Name = "Draw",
	Procedure = DFA_FLOAT,
	Speed = 250,
	Accel = 16,
	Decel = 16,
	FacetBase = 1,
	Length = 1,
	Delay = 3,
	NextAction = "Draw",
	StartCall = "Drawing",
},
WaitDraw = {
	Prototype = Action,
	Name = "WaitDraw",
	Procedure = DFA_FLOAT,
	Speed = 0,
	Accel = 0,
	Decel = 0,
	FacetBase = 1,
	Length = 1,
	Delay = 3,
	NextAction = "WaitDraw",
},

};
