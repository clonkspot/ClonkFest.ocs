/**
	Clonk Fest

	@author Pyrit
*/

static towin;			//Rounds that need to be won to finish the game
static maxwins;			//Maximum number of needed wins that can be selected.
static gameslist;		//Array with sectionnames
static score;			//Array with score. The index is the playernumber.
static currentsection;	//Section that's currently played


func Initialize()
{
	towin = 3;
	maxwins = 20;
	score=[];
	gameslist = ["Pickers", "Tools", "Molay"];
	currentsection = "Lobby";
	
	//Environment of the lobby
	CreateEnvironmentObjects("Temperate");
	CreateObject(Environment_Celestial);
	var time = CreateObject(Environment_Time);
	time->SetTime(60*20);
	time->SetCycleSpeed(20);
}

func InitializePlayer(iPlr)
{
	//Set zoom
	SetPlayerZoomByViewRange(iPlr, LandscapeWidth()/2, LandscapeHeight()/2, PLRZOOM_LimitMax|PLRZOOM_Direct);
	var clonk = GetCrew(iPlr);
	
	//Shows a message that tells you how many rounds you have to win
	CustomMessage(Format("@You need to win %d rounds for victory!", towin), nil, NO_OWNER, 100,100, 0, GUI_MenuDeco, Clonk);
	
	//Host gets to select how many wins you have to achieve
	if(iPlr==0)
		{
			clonk->CreateMenu(Nugget, nil, nil, "Rounds to win...", nil, nil, true);
			clonk->AddMenuItem("Increase", "Increase", Nugget);
			clonk->AddMenuItem("Decrease", "Decrease", Rock);
			clonk->AddMenuItem("Done!", "Done", Icon_Ok);
		}
		
}

func Increase(one, two)
{
	//If the upper limit is reached, the host hears a click, but towin doesn't increase
	if(towin == maxwins)
	{
		Sound("SoftTouch2", true, 100, 0);
		return;
	}
	
	//Else the number is increased, everyone hears a click and the message is updated
	towin++;
	Sound("SoftTouch2", true);
	CustomMessage(Format("@You need to win %d rounds for victory!", towin), nil, NO_OWNER, 100,100, 0, GUI_MenuDeco, Clonk);
}

func Decrease(one, two)
{
	//If the bottom limit is reached, the host hears a click, but towin doesn't decrease
	if(towin == 1)
	{
		Sound("SoftTouch2", true, 100, 0);
		return;
	}
	
	//Else the number is decreased, everyone hears a click and the message is updated
	towin--;
	Sound("SoftTouch2", true);
	CustomMessage(Format("@You need to win %d rounds for victory!", towin), nil, NO_OWNER, 100,100, 0, GUI_MenuDeco, Clonk);
}

func Done(one, two)
{
	//Creates a scoreboard
	Scoreboard->Init([{key = "wins", title = Nugget, sorted = true, desc = true, default = Format("0/%d", towin), priority = 75}]);
	
	//fills the score array with 0 for each player and makes a row for each player
	for(var plr; plr < GetPlayerCount(); plr++)
	{
		score[plr] = 0;
  		Scoreboard->NewPlayerEntry(plr);
	}
	
	GetCursor(0)->CloseMenu();
	CustomMessage(Format("Gogogogoogogog!!!111"), nil, NO_OWNER, 100,100, 0, GUI_MenuDeco, Clonk);
	Schedule(nil, "LoadSection()", 40, 0);
}

global func LoadSection()
{
	//Picka a random index from the gameslist
	var rnd = Random(GetLength(gameslist));
	
	//Section to load is the game with that index
	var section = gameslist[rnd];
	
	//Oh no, the section is the game we are currently playing. Go back one index.
	if(section == currentsection)
		section = gameslist[rnd-1];
	
	LoadScenarioSection(section);
	currentsection = section;
	
	//Reset the colors
	ResetGamma(3);
	SetSkyAdjust(RGB(255,255,255));
	SetMatAdjust(RGB(255,255,255));
	
	//Give erery player a new clonk and reset wealth
	for (var i; i<GetPlayerCount(); i++)
	{
		var clnk = CreateObject(Clonk, 10, 10, i);
		clnk->SetOwner(i);
		clnk->MakeCrewMember(i);
		SetCursor(i, clnk);
		SetWealth(i, 0);
	}
	CreateObject(C4Id(section), 0, 0);
}

//Standard goal timer. The owner of the only surviving clonk wins the round.
global func FxGoalTimer()
{
	if(GetPlayerCount()>1)
	{
		if(1 == GetLength(FindObjects(Find_ID(Clonk), Find_Not(Find_Action("Dead")), Find_Not(Find_Func("HasProperty", "isGhost")))))
		{
			var cfwinner = FindObjects(Find_ID(Clonk), Find_Not(Find_Action("Dead")), Find_Not(Find_Func("HasProperty", "isGhost")))[0];
			AddScore(cfwinner->GetOwner());	
		}
	}
}

global func AddScore(int plr)
{
    score[plr]++;
    Scoreboard->SetPlayerData(plr, "wins", Format("%d/%d",score[plr], towin));
    
    //Has the player achieved enough score to win?
    if(score[plr]==towin)
    {
    	//Creates an array filled with all player numbers
    	var losers = [];
    	for(var iloser; iloser<GetPlayerCount(); iloser++)
    		PushBack(losers, iloser);
    		
    	//Removes the winner from the array
    	losers[plr] = nil;
    	RemoveHoles(losers);
    	
    	//Eliminates all the people that are still in the array
    	for(var loser in losers)
    		EliminatePlayer(loser);
    		
    	RemoveEffect("Goal");
    	Schedule(nil, "GameOver()", 39, 0);
    	return;
    }
    
    //If not, load the next minigame.	
    LoadSection();
}




