/*-- 
	Cloncque De Molay
	Author: Pyrit
	
	Another minigame
--*/
static i;
static positions;

protected func Initialize()
{
	AddEffect("Goal", nil, 100, 10, nil);
	AddEffect("Clock", nil, 100, 1);
	var brick = CreateObject(MovingBrick, RandomX(10,LandscapeWidth()-10), 308);
	brick->MoveHorizontal(10, LandscapeWidth()-10, 15);
	positions = [[30,87],[97,87],[166,74],[257,79]];
	SetSkyAdjust(RGB(255,128,0));
	SetMatAdjust(RGB(255,150,128));
	
	for(var plr; plr <GetPlayerCount(); plr++)
	{
		var XY=positions[Random(3)];
		GetCrew(plr)->SetPosition(XY[0],XY[1]);
		SetPlayerZoomByViewRange(i, LandscapeWidth()/2, LandscapeHeight()/2, PLRZOOM_LimitMax|PLRZOOM_Direct);	
	}
	
	return;
}


global func FxClockTimer(target, effect, effect_time)
{	
	
	if(effect_time%(40-BoundBy(i,0,39)) == 0)
		MakeSpark();
	
	if(effect_time%240 == 0)
		i++;
	
	//spark->SetXDir(targetX);
	//spark->SetYDir(targetY);
	//, Distance(targetX, spark->GetX(), targetY, spark->GetY())
	
	CreateParticle("Fire",RandomX(20, LandscapeWidth()-20),321,RandomX(-1,1),RandomX(-1,1),RandomX(25,50),RGB(255,255,255));
	CreateParticle("Fire",RandomX(20, LandscapeWidth()-20),321,RandomX(-1,1),RandomX(-1,1),RandomX(25,50),RGB(255,255,255));
	CreateParticle("Fire",RandomX(20, LandscapeWidth()-20),321,RandomX(-1,1),RandomX(-1,1),RandomX(25,50),RGB(255,255,255));
}

global func MakeSpark()
{	
	var borders = [[0,Random(LandscapeHeight())],[Random(LandscapeWidth()),10], [LandscapeWidth()-10, Random(LandscapeHeight())], [Random(LandscapeWidth()), LandscapeHeight()-10]];
	var border = borders[Random(4)];
	var spark = CreateObject(FireRock, border[0], border[1]);
	var clonk = FindObjects(Sort_Random(), Find_ID(Clonk), Find_Not(Find_Action("Dead")));
	var targetX = clonk[0]->GetX();
	var targetY = clonk[0]->GetY();
	spark->Launch(targetX, targetY);
}
