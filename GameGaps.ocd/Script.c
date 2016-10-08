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
func GetGameStartPos(int player, int start_index, int max_index) { return {x=LandscapeWidth()/2-10+Random(20), y=40}; }
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
		var xm = Random(wdt - 20) + 10, x;
		if (!i && Inside(x, wdt/2-15, wdt/2+15)) { --i; continue; } // not directly below start
		var x0 = xm-10, x1 = xm+9;
		var ay0 = y0, ay1 = y1;
		var by0 = y0, by1 = y1;
		while (!GBackSolid(x0,ay0)) ++ay0;
		while (!GBackSolid(x0,ay1)) --ay1;
		while (!GBackSolid(x0,by0)) ++by0;
		while (!GBackSolid(x0,by1)) --by1;
		DrawMaterialQuad("Tunnel-brickback", x0,ay0-4, x1+1,by0-4, x1+1,by1+5, x0,ay1+5, true);
		DrawMaterialQuad("Tunnelbrick-brick", x0,ay0, x1+1,by0, x1+1,by1+1, x0,ay1+1, true);
	}
	return inherited(players);
}
