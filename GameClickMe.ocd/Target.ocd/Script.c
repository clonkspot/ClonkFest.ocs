/*-- ClickMe-Target --*/

static const ClickMe_Target_Defaultplane = 150;

local found;

func _a(string act) { return SetAction(act); }
func _m(int mod) { return SetClrModulation(mod); }
func _s(int scale) { return SetCon(scale); }
func _b(int blitmode) { return SetObjectBlitMode(blitmode); }
func _r(int r) { return SetR(r); }
func _d(int dir) { return SetDir(dir); }

func Initialize()
{
	SetAction("Wipf");
	return true;
}

func LogData(prefix, suffix)
{
	var log_mod="", log_scale="", log_blitmode="", log_plane="", log_r="", log_dir="";
	var v = GetClrModulation();
	if (v && v!=0xffffffff) log_mod = Format("clrmod=0x%x,",v);
	v = GetCon();
	if (v && v!=100) log_scale = Format("scale=%d,",v);
	v = GetObjectBlitMode();
	if (v) log_blitmode = Format("blitmode=%d,",v);
	v = this.Plane;
	if (v!=ClickMe_Target_Defaultplane) log_plane = Format("plane=%d,",v);
	v = GetR();
	if (v) log_r = Format("r=%d,",v);
	v = GetDir();
	if (v) log_dir = Format("dir=%d,",v);
	var params = Format("%s%s%s%s%s%s", log_mod, log_scale, log_blitmode, log_plane, log_r, log_dir);
	return Log("%s{action=\"%s\",x=%d,y=%d,%s}%s", prefix??"", GetAction(), GetX(), GetY(), params, suffix??"");
}

func SetData(proplist data)
{
	SetAction(data.action ?? "Wipf");
	SetCon(data.scale ?? 100);
	SetClrModulation(data.clrmod);
	SetObjectBlitMode(data.blitmode);
	this.Plane = (data.plane ?? ClickMe_Target_Defaultplane);
	SetDir(data.dir);
	SetR(data.r);
	SetPosition(data.x, data.y);
	SetCategory(1); // force resort
	return true;
}

func IsValidTarget() { return !found; }


// Fading out

func OnFound(int plr)
{
	if (found) return false;
	found = true;
	SetClrModulation(0xffffffff);
	AddTimer(this.FadeOutTimer, 2);
	return true;
}

func FadeOutTimer()
{
	var mod = GetClrModulation();
	if (!mod) mod=0xffffffff;
	var high_bit = (mod<0);
	var alpha = ((mod&0x7fffffff) >> 24) + (high_bit*128) - 7;
	if (alpha<=0) return RemoveObject();
	SetClrModulation((alpha<<24) | (mod & 0xffffff)) >> 24;
	DoCon(5);
	return true;
}



// Properties

local ActMap = {
Wipf = {
	Prototype = Action,
	Procedure = DFA_NONE,
	Name = "Wipf",
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 0,
	NextAction = "Wipf",
	X = 0,
	Y = 0,
	Wdt = 24,
	Hgt = 30,
},
};


local Name = "$Name$";
local Description = "$Description$";
local Plane = ClickMe_Target_Defaultplane;
