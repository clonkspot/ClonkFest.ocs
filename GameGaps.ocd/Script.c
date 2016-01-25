/*-- 
	Party game: Gaps
	Author: Sven2
	
	Reach the flag
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Gaps"; }
func GetGameClonkMaxEnergy() { return 10; }
func GetGameStartPos(int player) { return {x=LandscapeWidth()/2-10+Random(20), y=40}; }
func GetGameClonkMaxContents() { return 0; }
func GetGameRaceTarget() { return g_Goal_Flag; }

func InitGame(array players)
{
	SetPosition(0,0);
	var wdt = LandscapeWidth();
	for (var i=0; i<9; ++i)
	{
		var y0 = 45 + i * 40;
		var y1 = y0 + 15;
		var xm = Random(wdt - 20) + 10;
		if (!i && Inside(x, wdt/2-15, wdt/2+15)) { --i; continue; } // not directly below start
		for (var x=xm-10; x<xm+9; ++x)
		{
			var ay0=y0, ay1=y1;
			while (!GBackSolid(x,ay0)) ++ay0;
			while (!GBackSolid(x,ay1)) --ay1;
			DrawMaterialQuad("Tunnelbrick-brick", x,ay0, x+1,ay0, x+1,ay1+1, x,ay1+1, true);
		}
	}
	return inherited(players);
}
