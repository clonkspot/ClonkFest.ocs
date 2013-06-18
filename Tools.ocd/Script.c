/**
	Wrath Of The Tools

	@author Pyrit
*/

global func HorizonHeight()
{
	return(185);
}


func Construction()
{	
	//Standard goal (last man standing)
	AddEffect("Goal", nil, 100, 1, nil);
	
	//Make a brick floor
    for (var i = 0; i < LandscapeWidth(); i+=20)
         CreateObject(EarthBrick, i+10, HorizonHeight());
            
    //Grass!     
    PlaceGrass(75);
    
    //Clouds!
    Cloud->Place(5);
    SetWind(100);
    
    //Mushrooms
    for (var i = 0; i < 15; i++)
    	CreateObject(ColorMushroom, Random(LandscapeWidth()), HorizonHeight()-5).Plane = RandomX(399, 500);
    
    //Grass	
    for (var i = 0; i < 100; i++)
    	CreateObject(Grass, Random(LandscapeWidth()), HorizonHeight()-5).Plane = RandomX(399, 500);
    
     //Trees!   
     for (var i = 0; i < 10; i++)
         CreateObject(Tree_Coniferous, Random(LandscapeWidth()), HorizonHeight()-5);
     
     //Frame1() gets called in the first frame of the game. (After Objects were placed)
   	 Schedule(this, "Frame1()", 1, 0);       
}


func Frame1()
{   
	//Replacement for InitializePlayer()
	for(var plr; plr<GetPlayerCount(); plr++)
	{
		var index = 0, crew;
		while (crew = GetCrew(plr, index))
		{
			var x = Random(LandscapeWidth());
			crew->SetPosition(x , HorizonHeight()-15);
			var bow = CreateObject(Bow,10,1,plr);
			bow -> CreateContents(Arrow, 100);
			bow -> Enter(crew);
			index++;
		}

	//Add a timer that runs for ever
    AddEffect("CreateTool", this, 50, 45, this);

    SetPlayerZoomByViewRange(plr, LandscapeWidth(), nil, PLRZOOM_Direct | PLRZOOM_LimitMax);
	if(!GetPlrExtraData(plr, "AngryShovelsHighScore"))
		SetPlrExtraData(plr, "AngryShovelsHighScore", 0);
	}
	
   	
	 //This makes adjustments to the vegetation placement
    for(var tree in FindObjects(Find_ID(Tree_Coniferous)))
    {
        tree -> SetClrModulation(HSL(RandomX(25, 50),255,RandomX(180, 255)));
        tree -> SetR(RandomX(-15,15));
        tree -> SetPosition(tree->GetX(),135);
        tree.Plane = -1;
    }
    for(var grass in FindObjects( Find_ID(Grass)))
    {
        grass -> SetPosition(grass->GetX(),grass->GetY()-3);
        grass.Plane=-1;
        if(Random(2))
        grass.Plane=1;
    }
}


func FxCreateToolTimer(target, effect, effect_time)
{ 	
	if(Random(8))
		CreateTool(effect_time);
}

func CreateTool(int effect_time)
{	
	//Tools get faster with time
	var speed = RandomX(4000+effect_time,12000+effect_time);
	var tool = RandomTool();
	tool->SetYDir(speed, 8000);
	
	//Approx every tenth time a PowerUp gets created
	if(!Random(10))
	{
		//Determines wether it spawns left or right
		if(!Random(2))
			var X=1;
		else
		{
			var X=LandscapeWidth()-1;
			speed = -speed;
		}
		
		var powerUp = CreateObject(PowerUp, X, RandomX(25, 100));
		powerUp-> SetXDir(speed, 8000);
	}
	
	//Creates a lavachunk and flings it up
	if(!Random(5))
	{
		var bomb = CreateObject(LavaChunk, Random(LandscapeWidth()), LandscapeHeight()-1);
		bomb->Fling(RandomX(-3,3), -7);
	}
}

//Returns a random tool
global func RandomTool()
{
	if(!Random(5))
	{
		if(!Random(2))
			return CreateObject(AngrySword, SearchX(1), 8);
		else
			return CreateObject(AngryPickaxe, SearchX(5), 8);
	}
	return CreateObject(AngryShovel, SearchX(5), 10);
}

global func SearchX(likelyhood)	//Likelyhood is the chance, that X is directly above a clonk. 1 is always, e.g. 5 is every 5th time
{
	var X = Random(LandscapeWidth());
	
	if (!Random(likelyhood))
	{
		var clonk = FindObjects(Sort_Random(), Find_ID(Clonk), Find_Not(Find_Action("Dead")));
		if (clonk[0])	
		var X = clonk[0]->GetX()+RandomX(-2,2);
	}
	else
	
	if(!Random(2))
	{	
		//Tools get only created where there's a brick to destroy. Try 100 times to find such a place
		var tries = 0;
		var X = Random(LandscapeWidth());
		while (!GBackSolid(X, HorizonHeight()-5) && tries < 100)
		{
		var X = Random(LandscapeWidth());
		tries++;
		}
	}	
	return X;
}

