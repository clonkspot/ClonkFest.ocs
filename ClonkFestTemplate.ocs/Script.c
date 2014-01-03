/**
	Clonk Fest Template

	@author Pyrit, Sven2
*/

//
// WARNING!
//
// DO NOT EDIT THIS SCRIPT!
// Add your game to the Script.c of the contained GameTemplate.ocd file instead!

static g_ClonkFest_starting;

local is_game_over;

func InitializeMap(map)
{
}

func InitializePlayer(int plr)
{
	// Scoreboard setup
	Scoreboard->NewPlayerEntry(plr);
	// Delayed start of fest
	if (!g_ClonkFest_starting)
	{
		g_ClonkFest_starting = true;
		Schedule(nil, "GameCall(\"InitFest\")",1,1);
	}
}

func RemovePlayer(int plr)
{
	if (!is_game_over) Scoreboard->RemovePlayerEntry(plr);
}

func InitFest()
{
	// Let the fest begin! With a random game...
	var iplr=GetPlayerCount(C4PT_User);
	while (iplr--)
	{
		var plr = GetPlayerByIndex(iplr, C4PT_User);
		var crew = GetCrew(plr);
		if (crew) crew->RemoveObject();
	}
	var fest = CreateObject(Goal_ClonkFest);
	fest->InitFest();
	var game_id = fest->GetRandomGame();
	if (!game_id) FatalError("No game found! Did you screw up the template?");
	var game = CreateObject(game_id);
	if (!game) FatalError("Game could not be created! Did you screw up the template?");
	game->InitGameBase();
}

func OnGameFinished(array winners)
{
	Log("Round over.");
	is_game_over = true;
	var iplr=GetPlayerCount(C4PT_User);
	while (iplr--)
	{
		var plr = GetPlayerByIndex(iplr, C4PT_User);
		if (GetIndexOf(winners, iplr)<0)
			EliminatePlayer(plr);
		else
			Log("Winner: %s", GetTaggedPlayerName(plr));
	}
	GameOver();
}

func IsTemplate() { return true; }