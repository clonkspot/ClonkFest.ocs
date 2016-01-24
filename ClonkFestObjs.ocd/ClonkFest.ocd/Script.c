/*-- 
	Clonk fest main game
	Author: Sven2
--*/

//#include Library_Goal - lieber nur ein Spielziel

local games;
local next_game; // set if a specific game is called next
local score;
local score_to_win;
local fest_winners;
local open_games;

/* Initialization */

func Initialize()
{
	// Build game list
	games = [];
	var def,i,n_games;
	while (def = GetDefinition(i++))
		if (def->~IsGame() && def != GameBase)
			games[n_games++] = def;
	Log("Loaded %d games.", n_games);
	// Status
	this.Visibility = VIS_None;
	return _inherited(...);
}

func InitializePlayer(int plr)
{
	if (score)
	{
		score[plr] = 0;
		Scoreboard->NewPlayerEntry(plr);
		Scoreboard->SetPlayerData(plr, "wins", Format("%d/%d",score[plr], score_to_win));
	}
	return _inherited(plr, ...);
}

func RemovePlayer(int plr)
{
	if (score && !fest_winners) // if fest_winners is set, party is over - leave entries there for comparison
	{
		Scoreboard->RemovePlayerEntry(plr);
	}
	return _inherited(plr, ...);
}


/* Game interface */ 

func InitFest()
{
	for (var game in games) game->~InitFest();
	return true;
}

func GetRandomGame()
{
	var n = GetLength(games);
	if (!n) return nil;
	return games[Random(n)];
}

func StartFest()
{
	score = [];
	score_to_win = Max(GetLength(games) * 2 / 3,1);
	open_games = games[:];
	Scoreboard->Init([{key = "wins", title = Nugget, sorted = true, desc = true, default = Format("0/%d", score_to_win), priority = 75}]);
	for (var i=0; i<GetPlayerCount(C4PT_User); ++i)
	{
		var plr = GetPlayerByIndex(i,C4PT_User);
		Scoreboard->NewPlayerEntry(plr);
		Scoreboard->SetPlayerData(plr, "wins", Format("%d/%d",score[plr], score_to_win));
	}
	FestMessage(Format("$StartFest$", score_to_win));
	ScheduleCall(nil, Global.ClonkFest_NextGame, 300, 1, this);
	return true;
}

func OnGameFinished(array winners)
{
	var done;
	for (var winner in winners)
	{
		score[winner]++;
		Scoreboard->SetPlayerData(winner, "wins", Format("%d/%d",score[winner], score_to_win));
		if (score[winner] >= score_to_win) done = true;
	}
	if (done)
		OnFestFinished();
	else
	{
		FestMessage(Format("$WinGame$", PlrArray2String(winners)));
		//Log("OnGameFinished this %v games: %v", this, games);
		ScheduleCall(nil, Global.ClonkFest_NextGame, 200, 1, this);
	}
	return true;
}

func GetPlayerScore(int plr)
{
	if (!score) return 0;
	return score[plr] ?? 0;
}

func GetScoreToWin() { return score_to_win; }

global func ClonkFest_NextGame(object clonk_fest)
{
	// Reroute through scheduled global effect to prevent crash when loading section
	return clonk_fest->NextGame();
}

func NextGame()
{
	// Determine next game
	var game_id;
	// Was there a wish?
	if (next_game)
	{
		game_id = next_game;
		next_game = nil;
	}
	else
	{
		// Otherwise, pick at random
		if (!open_games || !GetLength(open_games)) open_games = games[:];
		var n_open = GetLength(open_games);
		var idx = Random(n_open);
		game_id = open_games[idx];
		--n_open;
		if (idx < n_open) open_games[idx] = open_games[n_open];
		SetLength(open_games, n_open);
	}
	// Start it!
	var game = CreateObject(game_id);
	game->InitGameBase();
}

func SetNextGame(new_next_game, by_player)
{
	Log("%s sets next game to %s!", GetTaggedPlayerName(by_player), new_next_game->GetName());
	Sound("UI::Ding", true);
	next_game = new_next_game;
	return true;
}


func OnFestFinished()
{
	var iplr=GetPlayerCount(C4PT_User);
	fest_winners = [];
	while (iplr--)
	{
		var plr = GetPlayerByIndex(iplr, C4PT_User);
		if (score[plr] < score_to_win)
			EliminatePlayer(plr);
		else
		{
			fest_winners[GetLength(fest_winners)] = plr;
		}
	}
	FestMessage(Format("$WinFest$", PlrArray2String(fest_winners)));
	ScheduleCall(this, Global.GameOver, 200);
	return true;
}

func FestMessage(string msg)
{
	return CustomMessage(Format("<c ffff00>$FestHost$:</c> %s", msg), nil, NO_OWNER, 5,10, 0xffffff, GUI_MenuDeco, this, MSG_HCenter | MSG_WidthRel | MSG_XRel | MSG_YRel, 80);
}



/* Definition */

local Name = "$Name$";
local Description = "$Description$";
