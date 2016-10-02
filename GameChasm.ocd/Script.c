/*-- 
	Party game: Chasm
	Author: Sven2
	
	Reach the goal flag!
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Chasm"; }
func GetGameClonkMaxEnergy() { return 5; }
func GetGameStartPos(int player) { return {x=40, y=270}; }
func GetGameTimeLimit() { return 180; }
func GetGameClonkMaxContents() { return 1; }
func GetGameRaceTarget() { return g_Goal_Flag; }

public func InitGame(array players)
{
	SetPosition(0,0);
	var chest = FindObject(Find_ID(Chest));
	if (chest)
	{
		for (var w in players)
		{
			var wb = chest->CreateContents(WindBag);
			if (wb) wb->AddRestoreMode(chest, chest->GetX(), chest->GetY());
		}
	}
	var n = 25;
	while (n) if (PlaceBrick()) --n;
	RemoveAll(Find_ID(Rock));
	return true;
}

private func PlaceBrick()
{
	var x0=100, x1=500, y0=120, y1=460;
	var x = x0+Random(x1-x0), xe;
	var y = y0+Random(y1-y0), ye;
	var l = (50+Random(100));
	var dir = Random(2), dx=0, dy=0;
	var sz = BoundBy((y-y0) * 4 / (y1-y0) + Random(2), 1, 4);
	Log("A %v, %v, %v, %v", x, y, l, dir);
	if (dir)
	{
		xe = Min(x + l, x1-1);
		x = Max(x - l, x0);
		++dx;
		ye = y;
	}
	else
	{
		ye = Min(y + l, y1-1);
		y = Max(y - l, y0);
		++dy;
		xe = x;
	}
	Log("%v, %v, %v, %v, %v, %v", x, y, xe, x, ye, y);
	if (FindObject(Find_ID(Rock), Find_AtRect(x-5, y-5, xe-x+10, ye-y+10)))
		return nil;
	var brick = CreateObject(MovingBrick, x+(4-sz)*5, y);
	if (brick)
	{
		if (dir) brick->MoveHorizontal(x, xe, 15); else brick->MoveVertical(y, ye, 15);
		brick->SetSize(sz);
		for (var c=0; c<Max(xe-x, ye-y); c += 15) CreateObject(Rock, x+dx*c, y+dy*c)->SetCategory(1);
	}
	return brick;
}
