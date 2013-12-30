/**
	Clonk Fest

	@author Pyrit, Sven2
*/

static g_ClonkFest_starting;
static g_clonk_fest;

func Initialize()
{
	InitLobby();
	AddMsgBoardCmd("next", "g_clonk_fest->SetNextGame(Game_%s, %player%)");
	return true;
}

func InitializePlayer(int plr)
{
	PositionPlayerCrew(plr);
	// Delayed start of fest
	if (!g_ClonkFest_starting)
	{
		g_ClonkFest_starting = true;
		Schedule(nil, "GameCall(\"InitFest\")",1,1);
	}
}

func InitFest()
{
	// Let the fest begin! With a random game...
	var fest = g_clonk_fest = CreateObject(Goal_ClonkFest);
	if (!fest) return;
	fest->InitFest();
	fest->StartFest();
	return true;
}

func OnGameFinished(array winners)
{
	// Expected to be called from global effect!
	LoadLobby(winners);
	if (g_clonk_fest) g_clonk_fest->OnGameFinished(winners);
	}

func LoadLobby(winners)
{
	LoadScenarioSectionClonkFest("main");
	for (var iplr=0; iplr < GetPlayerCount(C4PT_User); ++iplr)
	{
		var plr = GetPlayerByIndex(iplr, C4PT_User);
		var clonk = CreateObject(Clonk, Random(200)+250, 336, plr);
		clonk->MakeCrewMember(plr);
		SetCursor(plr, clonk);
		var was_winner = false;
		if (winners) if (GetIndexOf(winners, plr) >= 0) was_winner = true;
		PositionPlayerCrew(plr, was_winner);
	}
	return InitLobby();
}

func InitLobby()
{
	SetTemperature(100);
	SetClimate(100);
	DisableAllControls();
	return true;
}

func PositionPlayerCrew(int plr, bool was_winner)
{
	var crew = GetCrew(plr);
	if (!crew) return false;
	var last_score = 0;
	if (g_clonk_fest) last_score = g_clonk_fest->GetPlayerScore(plr);
	var max_score = 1;
	if (g_clonk_fest) max_score = Max(g_clonk_fest->GetScoreToWin(), 1);
	var score = Max(last_score + !!was_winner);
	crew->SetPosition(last_score*200/max_score+250+Random(10), 336-10);
	crew->SetDir(DIR_Right);
	if (was_winner)
	{
		crew->SetCommand("MoveTo", nil, score*200/max_score+250+Random(10), 336-10);
		crew->AddCommand("Wait", nil, 60,0, nil, 0,60);
		crew->Sound("FestWin*");
		Schedule(crew, "Jump()",5,1);
		Schedule(crew, "SetXDir()",6,1);
	}
	return true;
}