/*-- 
	Cloncque De Molay
	Author: Pyrit, Sven2
	
	Another minigame
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Pyrit"; }
func GetGameMinPlayers() { return 2; }
func GetGameMaxPlayers() { return nil; }
func GetGameSection() { return "Molay"; }
func GetGameStartPos(int player) { return [{x=30,y=87},{x=97,y=87},{x=166,y=74},{x=257,y=79}][Random(4)]; }
func IsGameLastManStanding() { return true; }
func GetGameClonkMaxContents() { return 0; }

local effect_time, spark_time, borders;

func InitGame(array players)
{
	var brick = CreateObjectAbove(MovingBrick, RandomX(10,LandscapeWidth()-10), 308);
	brick->MoveHorizontal(10, LandscapeWidth()-10, 15);
	SetSkyAdjust(RGB(255,128,0));
	SetMatAdjust(RGB(255,150,128));
	spark_time = 20;
	borders = [[0,Random(LandscapeHeight())],[Random(LandscapeWidth()),10], [LandscapeWidth()-10, Random(LandscapeHeight())], [Random(LandscapeWidth()), LandscapeHeight()-10]];
	DisableAllControls(true);
	return true;
}

func StartGame(array players)
{
	AddTimer(this.ClockTimer, 1);
	EnableAllControls(true);
	return true;
}


func ClockTimer()
{
	if(!(++effect_time%spark_time)) MakeSpark();
	if(!(effect_time%120)) spark_time = Max(spark_time-1, 1);
	
	var i=3;
	while(i--)
	{
		var x = Random(LandscapeWidth()-40)+20, y = Random(LandscapeHeight()-40)+20;
		CreateParticle("Fire", x,y, PV_Random(-10, +10), PV_Random(-10, +10), 10+Random(30), Particles_FireTrail(), 1);
	}
	return true;
}

func MakeSpark()
{
	var x,y;
	if (Random(2))
	{
		x = Random(LandscapeWidth());
		y = (LandscapeHeight()-1)*Random(2);
	}
	else
	{
		x = (LandscapeWidth()-1)*Random(2);
		y = Random(LandscapeHeight());
	}
	var spark = CreateObjectAbove(FireRock, x,y);
	var clonks = FindObjects(Find_ID(Clonk), Find_Not(Find_Action("Dead")), Find_Not(Find_Func("IsGhost")));
	var clonk = clonks[Random(GetLength(clonks))];
	if (clonk) spark->Launch(clonk->GetX(), clonk->GetY());
	return true;
}
