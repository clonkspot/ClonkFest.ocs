/*
	Camera
	Fix player view to this object
	
	@authors Sven2
*/

static g_camera; // singleton

func Initialize()
{
	if (g_camera) FatalError("OMG two cameras!");
	g_camera = this;
	// Make action modifyable
	this.ActMap = {Prototype = Camera.ActMap };
	this.ActMap.Fly = {Prototype = Camera.ActMap.Fly };
	SetAction("Fly");
	for (var i=0; i<GetPlayerCount(C4PT_User); ++i)
		SetPlrView(GetPlayerByIndex(i, C4PT_User), this);
	SetPlayerViewLock(NO_OWNER, true);
}


/* Fixed view */

global func SetPlrView(int plr, object target)
{
	// view is always on the camera
	if (g_camera) if (!target || target == g_camera) return true;
	return inherited(plr, target, ...);
}

// view is always on the camera
global func ResetCursorView(int plr)
{
	if (g_camera) return true;
	return inherited(plr, ...);
}


/* Object data */

// This is an environment object (e.g., shouldn't be target for hooks and stuff)
func IsEnvironment() { return true; }

local ActMap = {
	Fly = {
		Prototype = Action,
		Name = "Fly",
		Procedure = DFA_FLOAT,
		Speed = 100,
		Accel = 16,
		Decel = 16,
		X = 0,
		Y = 0,
		Wdt = 1,
		Hgt = 1,
		Length = 1,
		Delay = 0,
		NextAction = "Fly",
	},
};
local Name = "Camera";
