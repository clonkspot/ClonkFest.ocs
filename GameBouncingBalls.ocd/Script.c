/*-- 
	Party game: Bouncing balls
	Author: Sven2
	
	Find the exit!
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "BouncingBalls"; }
func GetGameClonkType() { return BouncingBall; }
func GetGameClonkMaxEnergy() { return BouncingBall.MaxEnergy; }
func GetGameStartPos(int player) { return {x=Random(LandscapeWidth()-100)+50, y=Random(LandscapeHeight()-100)+50}; }
func GetGameClonkMaxContents() { return 0; }
func IsGameLastManStanding() { return true; }

func InitGame(array players)
{
	SetSkyAdjust(0xff202040);
	return true;
}

local time, borders;

func StartGame(array players)
{
	time = 0;
	AddTimer(this.Timer, 30);
	var wdt = LandscapeWidth(), hgt = LandscapeHeight();
	var m = 15; // border margin
	borders = [
		{ x=m,       xl=wdt-2*m, y=0,       yl=0,       d=+1, nx=0,  ny=+1 }, // top
		{ x=wdt-1,   xl=0,       y=m,       yl=hgt-2*m, d=+1, nx=-1, ny=0  }, // right
		{ x=wdt-m-1, xl=wdt-2*m, y=hgt-1,   yl=0,       d=-1, nx=0,  ny=-1 }, // bottom
		{ x=0,       xl=0,       y=hgt-m-1, yl=hgt-2*m, d=-1, nx=+1, ny=0  }, // left
	];
	curr_wall_dir = -1; // first wall will be from top or bottom
	wall_time = -1;
	return true;
}

local curr_wall_dir;
local wall_time;

func Timer()
{
	++time;
	var n = 1+Random(time/80);
	if (Random(18)<n && time-wall_time > 3 && time > 4)
	{
		// Schedule next wall
		curr_wall_dir = (curr_wall_dir + 1 + Random(2)*2) % 4; // next wall always perpendicular to previous
		wall_time = time + 3;
	}
	else if (time == wall_time)
	{
		// Creater scheduled wall
		LaunchWall(curr_wall_dir);
	}
	while (n--)
	{
		var b = Random(4);
		if (b == curr_wall_dir && time-wall_time<3) continue; // no regular rocks near wall
		b = borders[b];
		// Create individual rocks
		LaunchFireRock(b.x+Random(b.xl)*b.d, b.y+Random(b.yl)*b.d, b.nx*10+Random(5)-2, b.ny*10+Random(5)-2);
	}
	return true;
}

func LaunchWall(wall_dir)
{
	// Launch big wall of rocks
	var dist = 25;
	var gap_size = 2; // number of rocks to skip for gap
	var clr = RndColor();
	var b = borders[wall_dir];
	var gap_start = Random(b.xl/dist+b.yl/dist-2)+1;
	var i = 0;
	// Depending on wall direction, one of these loops has only one iteration
	for (var y=b.y; y*b.d<=b.d*b.y+b.yl; y += dist*b.d)
		for (var x=b.x; x*b.d<=b.d*b.x+b.xl; x += dist*b.d)
		{
			if (!gap_start--) if (gap_size--) { ++gap_start; continue; }
			LaunchFireRock(x,y, b.nx*10, b.ny*10, clr);
		}
	return true;
}

func LaunchFireRock(int x, int y, int vx, int vy, int clr)
{
	if (!clr) clr = RndColor();
	var rock = CreateObjectAbove(FireRock);
	if (rock)
	{
		rock.Plane = -1;
		rock->SetR(Random(360));
		rock->Launch2(x,y,vx,vy, clr);
	}
	return rock;
}

func RndColor() { return HSL(Random(256), 200+Random(56), 200+Random(56)); }

func OnGameFinished()
{
	// Normal race goal evaluation
	inherited(...);
	if (!GetLength(game_winners)) return 1; // nobody found the goal
	// Goal found - effects at winner Clonks
	ScheduleCall(this, this.EndSequence, 25, 10, game_winners);
	return 125;
}

func EndSequence(winners)
{
	for (var plr in winners)
	{
		var crew = GetCrew(plr);
		if (crew)
		{
			crew->Sound("BalloonPop");
			crew->CreateParticle("MagicSpark", RandomX(-15,15),RandomX(-15,15), PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Colored(Particles_Spark(),0xff8000,0xffff00), 15);
		}
	}
	return true;
}
