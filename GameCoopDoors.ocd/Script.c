/*-- 
	Coop door game
	Author: Luchs
--*/

#include GameBase

/* Overloads by games */

func GetGameAuthor() { return "Luchs"; }

// Section of landscape to be used for this game
// Multiple games may share the same map and a map may have multiple maps.
func GetGameSection() { return "Empty"; }

func Initialize()
{
	doorcount = RandomX(4, 7);
	return inherited(...);
}

// Callback function to be overloaded for custom game initialization
// This is called after section load and all generic game initialization (Clonk placement, player properties set, etc.)
// players is an array of player numbers of players that participate. Do not assume that all players take part.
func InitGame(array players)
{
	// Determine switch connections.
	// For every door, we ensure that there is at least one switch before and
	// after the door, and that either the upper or the lower corridor has a
	// switch both before and after the door.

	// First, initialize the switch_connections array.
	switch_connections = CreateArray(doorcount+1);
	for (var i = 0; i <= doorcount; i++)
		// upper, lower
		switch_connections[i] = [[], []];
	// Second, distribute connections for each door.
	for (var i = 0; i < doorcount; i++)
	{
		var has_before = [false, false];
		var has_after = [false, false];
		while (!Any(has_before) || !Any(has_after)
			|| !((has_before[0] && has_after[0]) || (has_before[1] && has_after[1])))
		{
			var r = Random(100);
			var switch, ul;
			var ul = r % 2;
			// TODO: Sometimes create multiple connections?
			if (r < 50) // before
			{
				switch = Random(i);
				has_before[ul] = true;
			}
			else
			{
				switch = 1 + i + Random(doorcount - i);
				has_after[ul] = true;
			}
			if (Last(switch_connections[switch][ul]) != i)
				PushBack(switch_connections[switch][ul], i);
		}
	}
	initial_door_state = CreateArray(doorcount);
	for (var i = 0; i < doorcount; i++)
		initial_door_state[i] = Random(2);

	// Assign players in pairs to corridors.
	ShuffleArray(players);
	var playercount = GetLength(players);
	var n = GetCorridorCount();
	corridors = CreateArray(n);
	for (var i = 0; i < n; i++)
	{
		var c = InitCorridor(padding*mapzoom, (padding + i*(2*corridor_height + padding))*mapzoom);
		corridors[i] = c;
		var p1 = PopBack(players);
		var p2;
		// Only two players => have them compete.
		if (playercount > 2)
			p2 = PopBack(players);
		c.players = [p1, p2];
		var c1 = GetCrew(p1), c2;
		if (p2 == nil)
		{
			PopBack(c.players);
			c2 = CreateObject(GetGameClonkType(), 0, 0, p1);
			c2->MakeCrewMember(p1);
		}
		else
			c2 = GetCrew(p2);
		c1->SetPosition(c.wipf->GetX(), c.wipf->GetY() - 5);
		c2->SetPosition(c.idol->GetX(), c.idol->GetY());
	}
	DisableAllControls(true);
	return true;
}

// Array helper functions
func Last(array a) { return a[GetLength(a)-1]; }
func Or(bool a, bool b) { return a || b; }
func Any(array a) { return Reduce(a, Or, false); }

// Callback function when game is finished
// Call stuff like SetGameWinners() here.
func OnGameFinished()
{
	var winners = [];
	for (var c in corridors)
	{
		if (c->IsWin())
		{
			winners[GetLength(winners):] = c.players;
		}
	}
	SetGameWinners(winners);
	return true;
}

// Helper functions:
// GetGamePlayers() - return array of player numbers of players who play in the game
// GetLivingGamePlayers() - return array of players that aren't ghosts
// GhostPlayer(int player) - remove crew of player and turn cursor into a ghost

// SetGameWinners(array winners) - store winners of this game
// FinishGame() - mark game as ended and start next


/* Optional overloads */

// Set this to number of seconds if the game should end automatically after a set time
func GetGameTimeLimit() { return 240; }

local mapzoom = 8;
local padding = 5; // outer space
local wall_wdt = 1; // width of brick walls
local left_platform = 15; // size of the starting platform
local right_open = 10; // size of the platform gap to the right
local middle_platform = 10; // size of the middle platforms, including the gaps
local doorcount = 5; // number of doors
local corridor_height = 5; // StoneDoor->GetDefHeight() / mapzoom;
local switch_connections; // Array of connections for each switch: [[[0, 1], [0, 2]]] => first upper switch is connected to doors 0 and 1, first lower to 0, 2
local initial_door_state; // Array of initial door states (0/1 = open/closed).
local corridors; // Array of CorridorEffect

func GetCorridorCount()
{
	var n = GetLength(GetGamePlayers());
	// Have two players compete.
	if (n == 2) return 2;
	return n / 2 + n % 2;
}

local GameSpinWheel = new SpinWheel
{
	doors = nil,
	Initialize = func()
	{
		doors = [];
		Call(SpinWheel.Initialize);
	},
	ControlUp = func(object clonk)
	{
		// Toggle all doors.
		for (var door in doors)
		{
			if (door->IsOpen())
				door->CloseDoor();
			else if (door->IsClosed())
				door->OpenDoor();
		}
		Sound("Structures::StoneGate::Chain");
		SetAction("SpinRight");
	},
	ControlDown = func(object clonk)
	{
		return ControlUp(clonk);
	},
};

local CorridorEffect = new Effect
{
	win_distance = 0,
	wipf = nil, idol = nil,
	players = nil,

	Construction = func(object wipf, object idol)
	{
		this.wipf = wipf;
		this.idol = idol;
		win_distance = Idol->GetDefHeight() / 2;
		players = [];
	},

	IsWin = func()
	{
		return ObjectDistance(wipf, idol) < win_distance;
	},

	Timer = func()
	{
		if (IsWin())
			Target->FinishGame();
	},
};

func InitCorridor(int offx, int offy)
{
	var x = offx + (wall_wdt + left_platform) * mapzoom - StoneDoor->GetDefWidth()/2;
	var y = offy + (wall_wdt + corridor_height) * mapzoom;
	var spin_y = y - wall_wdt*mapzoom;
	var doors = [], wheels = [];
	for (var i = 0; i <= doorcount; i++)
	{
		var xpos = x + i*middle_platform*mapzoom;
		if (i < doorcount)
			doors[i] = CreateObjectAbove(StoneDoor, xpos, y);
		
		wheels[i] = [
			CreateObjectAbove(GameSpinWheel, xpos - middle_platform*mapzoom / 2, spin_y),
			CreateObjectAbove(GameSpinWheel, xpos - middle_platform*mapzoom / 2, spin_y + corridor_height*mapzoom)
		];
	}
	// Connect wheels to doors.
	for (var i = 0; i <= doorcount; i++)
		for (var ul in [0, 1])
		{
			if (GetLength(switch_connections[i][ul]) == 0)
				wheels[i][ul]->RemoveObject();
			for (var door in switch_connections[i][ul])
				PushBack(wheels[i][ul].doors, doors[door]);
		}
	// Close some of the doors.
	for (var i = 0; i < doorcount; i++)
		if (initial_door_state[i])
			doors[i]->OpenDoor();
		else
			doors[i]->CloseDoor();

	// Decoration
	CreateObjectAbove(Vine, x + mapzoom*(doorcount*middle_platform + right_open/2), offy + mapzoom*wall_wdt + Vine->GetDefHeight());

	// Create Wipf and Statue
	x -= mapzoom*left_platform*3/4;
	y -= mapzoom*wall_wdt;
	var wipf = CreateObjectAbove(Wipf, x, y);
	var idol = CreateObjectAbove(Idol, x, y + mapzoom*corridor_height);
	return CreateEffect(CorridorEffect, 1, 10, wipf, idol);
}

func InitializeMap(proplist map)
{
	var corridor_width = left_platform + right_open + doorcount*middle_platform;
	var n = GetCorridorCount();
	map->Resize(padding*2 + corridor_width, padding*2 + n * (corridor_height*2 + padding));

	var corridor = map->CreateLayer("Tunnel-Brickback", corridor_width, corridor_height*2 + 1);
	DrawCorridor(corridor, doorcount);

	for (var i = 0; i < n; i++)
	{
		map->Blit({ Algo = MAPALGO_Offset, OffX = padding, OffY = padding + (corridor_height*2 + padding) * i, Op = corridor });
	}
	return true;
}

func DrawCorridor(proplist map, int doorcount)
{
	map->Draw("Brick", { Algo = MAPALGO_Border, Wdt = wall_wdt, Op = { Algo = MAPALGO_Rect, X = 0, Y = 0, Wdt = map.Wdt, Hgt = map.Hgt } });
	var floor = map->CreateLayer("Brick", map.Wdt - right_open, wall_wdt);
	// openings for the doors
	floor->Draw("Transparent", { Algo = MAPALGO_And, Op = [
	    { Algo = MAPALGO_Lines, X = wall_wdt, Y = 0, OffX = left_platform, Distance = (floor.Wdt - left_platform) / doorcount },
	    { Algo = MAPALGO_Rect, X = left_platform, Y = 0, Wdt = floor.Wdt, Hgt = floor.Hgt }
	] });
	map->Blit({ Algo = MAPALGO_Offset, OffX = 0, OffY = map.Hgt / 2, Op = floor });
}

/* Basic information - set localizaed name and description in string tables */

local Name = "$Name$";
local Description = "$Description$";
