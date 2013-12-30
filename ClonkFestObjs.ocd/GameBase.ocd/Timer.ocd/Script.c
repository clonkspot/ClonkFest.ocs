/**
	HUD Timer
	Displays a countdown in the HUD.
	
	@authors Sven2
*/

local callback_object; // object to be notified when time is up
local time; // remaining time, in seconds

protected func Initialize()
{
	// Set parallaxity
	this.Parallaxity = [0, 0];
	// Set visibility
	this.Visibility = VIS_All;
	return true;
}

public func SetTime(int new_time, object new_callback_object)
{
	// Kill previous timer
	RemoveTimer(this.Timer);
	// Register new timer and do initial update if a timer was set
	time = new_time;
	callback_object = new_callback_object;
	if (time)
	{
		AddTimer(this.Timer, 37);
		++time; Timer();
	}
	else
	{
		// no timer active.
		CustomMessage("", this, NO_OWNER, 0, 90);
	}
	return true;
}

public func Timer()
{
	--time;
	var clr;
	if (time < 20)
	{
		clr = 0xff0000;
		Sound("Click", true);
		if (time>0)
			CustomMessage(Format("@<c ff0000>00:%02d</c>",time), nil, NO_OWNER, 0,-100);
		else
			CustomMessage("", nil, NO_OWNER, 0,-100);
	}
	else
		clr = 0xff00;
	var mm = time / 60;
	var ss = time % 60;
	CustomMessage(Format("@<c %x>%02d:%02d</c>",clr,mm,ss), this, NO_OWNER, 0, 90);
	if (time<=0)
	{
		RemoveTimer(this.Timer);
		if (callback_object) callback_object->~OnTimeUp();
	}
	return true;
}
