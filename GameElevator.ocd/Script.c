/*-- 
	Party game: Elevator
	Author: Sven2
	
	Avoid falling down.
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Elevator"; }
func GetGameClonkMaxEnergy() { return 10; }
func GetGameStartPos(int player) { return {x=140+Random(20), y=40}; }
//func GetGameTimeLimit() { return 180; }
func GetGameClonkMaxContents() { return 2; }
func IsGameLastManStanding() { return true; } // Game should end automatically if only one player is left alive

func InitGame(array players)
{
	DisableAllControls(true);
	return true;
}

func StartGame(array players)
{
	for (var brick in FindObjects(Find_ID(MovingBrick)))
	{
		brick->SetMoveSpeed(50);
		brick->SetComDir(COMD_Down);
	}
	AddTimer(this.Timer, 28);
	EnableAllControls(true);
	return true;
}

local time;

func Timer()
{
	// Create bricks regularly
	// As time progresses, bricks get smaller and items get stronger.
	// After a longer time, bricks also get faster.
	++time;
	var wdt = LandscapeWidth() - 100;
	var x = (time%2)*(wdt/2) + Random(wdt/2) + 50;
	var brick_size = Max(4-Random(1+time/20), 1);
	var brick_off = (4-brick_size)*5;
	var brick = CreateObject(MovingBrick, x+brick_off, 8, NO_OWNER);
	if (brick)
	{
		brick->SetSize(brick_size);
		var brick_speed = 50;
		if (time > 120) brick_speed += Random((time-120)/3); // sudden death mode :D
		brick->SetMoveSpeed(brick_speed);
		brick->SetComDir(COMD_Down);
		// Items on some bricks
		if (!Random(3))
		{
			var item_types;
			if (Random(6))
				item_types = [Rock, Firestone, Dynamite, Arrow]; // common
			else
				item_types = [Firestone, WindBag, Sword, Bow]; // rare
			var item_type = item_types[Random(Min(1+time/25, 4))];
			if (item_type == Firestone && brick_size == 1) x+=3; // vertices are weird. they tend to fall off.
			CreateObject(item_type, x, 0, NO_OWNER);
		}
	}
}
