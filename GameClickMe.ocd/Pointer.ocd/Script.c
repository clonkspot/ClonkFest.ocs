/*-- ClickMe-Pointer --*/

/* Use */

local game_object;

func SetGameObject(object agame_object)
{
	game_object = agame_object;
	return true;
}

func ControlUse(object clonk, int x, int y)
{
	game_object->OnClickMe(clonk->GetOwner(), x+GetX(), y+GetY());
	return true;
}


/* Prevent departure */

local clonk;

func Entrance(object new_container)
{
	if (!clonk) clonk = new_container;
	else ScheduleCall(this, "EnsureContainer", 1,1);
}

func Departure()
{
	if (clonk) ScheduleCall(this, "EnsureContainer", 1,1);
}

func EnsureContainer()
{
	if (clonk && Contained() != clonk) Enter(clonk);
	return true;
}


/* Properties */

local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";
local Collectible = 1;
