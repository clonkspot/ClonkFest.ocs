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
func GetGameClonkMaxContents() { return 2; }
func GetGameRaceTarget() { return g_Goal_Flag; }
