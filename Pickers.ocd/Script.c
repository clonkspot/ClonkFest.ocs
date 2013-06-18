/*-- 
	Berrypickers
	Author: Pyrit
	
	Another minigame
--*/

static pickerswinner;

protected func Initialize()
{
	//Smooth ground!
	DigFreeRect(0, 195, LandscapeWidth(), 6);
	
	//Grass!
	for (var i = 0; i < 100; i++)
    	CreateObject(Grass, i*5+RandomX(-5,5), 200+RandomX(-1,1)).Plane=RandomX(1, 499);
        
     //Trees!   
     for (var i = 0; i < 20; i++)
         CreateObject(Tree_Coniferous, i*20+RandomX(-15, 15), 205);
         
    //"Player Initializion"
    for(var plr; plr < GetPlayerCount(); plr++)
    {
    	GetCrew(plr)->SetPosition(Random(LandscapeWidth()), 188);
    	SetPlayerViewLock(plr, true);
		SetPlayerZoomByViewRange(plr, LandscapeWidth(), nil, PLRZOOM_Direct | PLRZOOM_LimitMax);
		var lorry = GetCrew(plr)->CreateObject(Lorry,0,0,plr);
		GetCrew(plr)->SetCommand("Grab", lorry);
		
		//Make 1 start berry for every player
		var berry = CreateObject(Sproutberry, RandomX(20, LandscapeWidth()-20), RandomX(150, 170));
		berry.i = 100;
		berry->SetCon(100);
		berry->AddTimer("StartWobble", RandomX(50, 100));
	}
         
    Schedule(this, "Frame1()", 1, 0);
    Schedule(this, "Frame15()", 15, 3);
	return;
}


func Frame1()
{
    //This makes adjustments to the vegetation placement
    for(var tree in FindObjects(Find_ID(Tree_Coniferous)))
    {
        tree -> SetClrModulation(HSL(RandomX(25, 50),255,RandomX(180, 255)));
        tree -> SetR(RandomX(-7,7));
        tree -> SetPosition(tree->GetX(),tree->GetY()-8);
        if(!Random(2))
		tree.Plane = RandomX (-20,-1);
		else
		tree.Plane = RandomX(1, 20);
        if(!Random(3)) tree -> CreateObject(Sproutberry, RandomX(-30, 30), RandomX(-40, 0));
    }
    DigFreeRect(0, 195, LandscapeWidth(), 6);
}

func Frame15()
{
	DigFreeRect(0, 195, LandscapeWidth(), 6);
}
