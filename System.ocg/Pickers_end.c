global func PickersEnd()
{	
	GameFreeze();	//Freeze current state of the game...
	Schedule(nil, "FocusWinner()", 100, 0);	//Focus the winner after 100 frames...
}

global func GameFreeze()

{
	for(var clonk in FindObjects(Find_ID(Clonk)))	//Put all clonks into a dummy clonk, so that they can't move anymore
	{
		var dummy = clonk->CreateObject(Clonk, 0, +5);
		clonk -> Enter(dummy);
	}
	
	for(var berry in FindObjects(Find_ID(Sproutberry)))	//Remove all timers from the berries and stop them from falling
	{
		berry->SetAction("Float");
		berry->SetYDir(0);
		berry->RemoveTimer("Grow");
		berry->RemoveTimer("StartWobble");
		berry->RemoveTimer("Wobble");
		berry->RemoveTimer("LimitSpeed");
	}
	
	for(var tree in FindObjects(Find_ID(Tree_Coniferous)))	//Trees don't grow new berries
	{
		tree->ClearScheduleCall();
		tree->RemoveTimer("MakeBerry");
	}
	
}

global func FocusWinner()
{
	for(var k=0; k<GetPlayerCount();k++)	//We just go through every player in the game
	{
		SetPlrView(k, GetCursor(pickerswinner));	//Focus their window on the winning clonk
		SetPlayerViewLock(k, 1);			//No screen scrolling anymore
		SetPlayerZoomByViewRange(k, nil, 170, PLRZOOM_LimitMin|PLRZOOM_LimitMax);	//Zoom in
	}
	Schedule(GetCursor(pickerswinner)->Contained(), "WinEat()", 25, 10);	//Let the winner do some eating animation...
	Schedule(nil, "EndGame()", 125, 0);	//In 125 frames, the game will be over
}

global func WinEat()
{
	SetAction("Eat");
	Sound("Munch1");
	Schedule(this, "Juice()", 9, 0);	//Juice with delay...
}

global func Juice()
{
	for(var j; j<15; j++)
		CreateParticleAtBone("Spark", "skeleton_head", [0, -3, 0], [RandomX(-10, 10), RandomX(-10, 10), RandomX(-10, 10)], 15, RGB(255,0,255));
}

global func EndGame()	//Ending the game by removing all the clonk's that didn't win
{
	AddScore(pickerswinner);
}



