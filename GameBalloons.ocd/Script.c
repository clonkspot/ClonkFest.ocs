/*-- 
	Party game: Balloons
	Author: Sven2
	
	Another Clonk Fest game.
--*/

#include GameBase

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Balloons"; }
func GetGameStartPos(int player, int start_index, int max_index) { return {x=20+Random(130), y=207-10}; }
func GetGameClonkMaxContents() { return 0; }
func GetGameTimeLimit() { return 300; }

local scores;
local target_score = 300;

func InitGame(array players)
{
	scores = [];
	Scoreboard->Init([{key = "game", title = GetID(), sorted = true, desc = true, default = "0", priority = 100}]);
	for (var plr in players)
	{
		scores[plr] = 0;
		Scoreboard->SetPlayerData(plr, "game", 0);
		var crew = GetCrew(plr);
		if (crew)
		{
			var catapult = crew->CreateObjectAbove(Catapult, 0, 10, plr);
			if (catapult)
			{
				catapult->SetObjectLayer(crew);
				crew->SetObjectLayer(crew);
				crew->SetCommand("Grab", catapult);
			}
		}
	}
	// no deactivation needed - just don't give flints or balloons
	return true;
}

local max_firestones = 5;
local cata_status_strings;

func StartGame(array players)
{
	// prepare catapult status messages
	cata_status_strings = CreateArray(max_firestones+1); cata_status_strings[0] = "";
	for (var i=1; i<=max_firestones; ++i) cata_status_strings[i] = Format("%s{{Firestone}}", cata_status_strings[i-1]);
	// add game timers
	AddTimer(this.CataTimer, 5);
	AddTimer(this.AmmoTimer, 80);
	AddTimer(this.BalloonTimer, 50);
	AddTimer(this.WindTimer, 50);
	return true;
}

func CataTimer()
{
	// Catapult status update
	for (var cata in FindObjects(Find_ID(Catapult), Find_AnyLayer()))
		CustomMessage(cata_status_strings[cata->ContentsCount()], cata, cata->GetOwner());
	return true;
}

func AmmoTimer()
{
	// Every catapult gets some new firestones
	var firestone;
	for (var cata in FindObjects(Find_ID(Catapult), Find_AnyLayer()))
		if (cata->ContentsCount() < max_firestones)
			if (firestone = cata->CreateContents(Rock))
			{
				firestone->SetObjectLayer(this);
				firestone.Hit = this.Firestone_Hit;
				firestone->SetClrModulation(GetPlayerColor(cata->GetOwner()));
			}
	// Update display
	CataTimer();
	return true;
}

// Called in projectile
func Firestone_Hit()
{
	Explode(20);
}

func BalloonTimer()
{
	var balloon = CreateObjectAbove(Balloon, 410+Random(160), LandscapeHeight()-1);
	if (balloon)
	{
		var size = 25 + Random(75);
		var speed = 100 + Random(300);
		var type = Random(Random(3)+1);
		var gfx = nil;
		if (type == 1 && !Random(4)) gfx = [GoldBar, Treasure, Nugget, Clonk, Flour, Sword][Random(6)];
		var multiplier = 1;
		if (type == 2) ++multiplier;
		if (size < 50) ++multiplier;
		if (size < 50 && speed > 300) multiplier += 3;
		if (gfx) ++multiplier;
		var speed_score = speed * speed / 250;
		var size_score = (150-size) * (150-size) / 100;
		var score = Max((speed_score * size_score * multiplier) / 2500, 5);
		score = score / 5 * 5;
		balloon->Init(this, type, gfx, score, size, speed);
		balloon->SetObjectLayer(this);
		var clr;
		if (score >= 100) clr = 0xffff00; else clr = 0xffffff;
		CustomMessage(Format("@<c %x>%d</c>", clr, score), balloon, NO_OWNER, 0, 31+GetCon()/10);
	}
	// Ballonschwemme!
	if (!Random(25))
	{
		ScheduleCall(this, this.BalloonTimer, 3+Random(3), 10+Random(10));
	}
	return true;
}

func OnBalloonPopped(int score, int plr)
{
	if (plr<0) return;
	scores[plr] += score;
	Scoreboard->SetPlayerData(plr, "game", scores[plr]);
	var crew = GetCrew(plr);
	if (crew)
	{
		var fm = CreateObjectAbove(FloatingMessage, crew->GetX() - GetX(), crew->GetY() - GetY(), NO_OWNER);
		if (fm)
		{
			var plr_clr = GetPlayerColor(plr);
			fm->SetColor(GetRGBaValue(plr_clr, 1), GetRGBaValue(plr_clr, 2), GetRGBaValue(plr_clr, 3));
			fm->FadeOut(1+score/25, 8);
			fm->SetSpeed(0, -4);
			fm->SetMessage(Format("%d</c>", score));
		}
	}
	if (scores[plr] >= target_score) FinishGame();
	return true;
}

func WindTimer()
{
	var wind = GetWind();
	return SetWind(BoundBy(wind + Random(3) - 1, -100, 10));
}

func OnGameFinished()
{
	RemoveTimer(this.CataTimer);
	RemoveTimer(this.AmmoTimer);
	RemoveTimer(this.BalloonTimer);
	RemoveTimer(this.WindTimer);
	ClearScheduleCall(this, this.BalloonTimer);
	// All players that have reached the target score
	var winners = [];
	for (var plr in GetGamePlayers())
		if (scores[plr] >= target_score)
			winners[GetLength(winners)] = plr;
	SetGameWinners(winners, true);
	if (!GetLength(winners)) return true;
	return true;
}

func RelaunchPlayer(int plr)
{
	// Ignore during section loading
	if (g_loading_section) return;
	// Just relaunch
	var crew = LaunchPlayerClonk(plr);
	var catapult = FindObject(Find_ID(Catapult), Find_Owner(plr));
	if (catapult && crew)
	{
		catapult->SetObjectLayer(crew);
		crew->SetObjectLayer(crew);
		crew->SetCommand("Grab", catapult);
	}
	return true;
}

local Name = "$Name$";
local Description = "$Description$";
