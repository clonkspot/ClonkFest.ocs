/*-- 
	Party game: Mouse maze
	Author: Sven2
	
	Find the exit!
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

local goal_cheese;
local map_zoom = 10;

static g_MouseMaze_seed;

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "MouseMaze"; }
func GetGameClonkType() { return MazeMouse; }
func GetGameClonkMaxEnergy() { return 42; }
func GetGameStartPos(int player) { return {x=entry_cave_x*map_zoom+map_zoom/2+0*RandomX(-20,20), y=entry_cave_y*map_zoom+map_zoom/2+0*RandomX(-20,20)}; }
func GetGameClonkMaxContents() { return 0; }
func GetGameTimeLimit() { return 300; }
func GetGameRaceTarget() { return goal_cheese; }
func GetGameMaxZoomRange() { return {x=400, y=300}; }

func InitGame(array players)
{
	// Brick blocks start until game is really started
	DrawMaterialQuad("Brick-brick1", entry_x*map_zoom+2,entry_y*map_zoom, entry_x*map_zoom+6,entry_y*map_zoom, entry_x*map_zoom+6,entry_y*map_zoom+map_zoom, entry_x*map_zoom+2,entry_y*map_zoom+map_zoom);
	// Goal
	goal_cheese = CreateObject(Cheese, exit_cave_x*map_zoom+map_zoom/2, exit_cave_y*map_zoom + map_zoom/2);
	return true;
}

func StartGame(array players)
{
	CreateParticle("MagicSpark", entry_x*map_zoom+4, PV_Random(entry_y*map_zoom, entry_y*map_zoom+map_zoom-1),PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Colored(Particles_Spark(),0xff8000,0xffff00), 15);
	DrawMaterialQuad("Tunnel-brickback", entry_x*map_zoom+2,entry_y*map_zoom, entry_x*map_zoom+6,entry_y*map_zoom, entry_x*map_zoom+6,entry_y*map_zoom+map_zoom, entry_x*map_zoom+2,entry_y*map_zoom+map_zoom);
	return true;
}

func OnGameFinished()
{
	// Normal race goal evaluation
	inherited(...);
	if (!GetLength(game_winners)) return 1; // nobody found the goal
	// Goal found - effects at winner Clonks
	ScheduleCall(this, this.EndSequence, 25, 10, game_winners);
	return 125;
}

func EndSequence(winners)
{
	for (var plr in winners)
	{
		var crew = GetCrew(plr);
		if (crew)
		{
			crew->Sound("BalloonPop");
			crew->CreateParticle("MagicSpark", RandomX(-15,15),RandomX(-15,15), PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Colored(Particles_Spark(),0xff8000,0xffff00), 15);
		}
	}
	return true;
}

/* Map */

local entry_x, entry_y, exit_x, exit_y, entry_cave_x, entry_cave_y, exit_cave_x, exit_cave_y;

func InitializeMap(proplist map)
{
	// Simple map generation algorithm
	// (I believe this is a variation of randomized Prim's algorithm)
	// Ensure unique seed for this game
	var n_rands = g_MouseMaze_seed++ * 5;
	while (n_rands--) Random(Random(99));
	// Maze size
	var wdt=30, hgt=30;
	// Maze start pos
	var sx=0, sy=0;
	// Direction helper array
	var directions = [[-1, 0], [+1,0], [0,-1], [0,+1]];
	// Initially, all walls are closed
	// passages_x: Right side of cells; passages_y: Bottom side; visited: Number of moves to reach this cell
	// (passages arrays are one larger than they need to be)
	var passages_x = CreateArray(wdt*hgt), passages_y = CreateArray(wdt*hgt), visited = CreateArray(wdt*hgt);
	// List of neighbour cells to be visited
	var open_x = CreateArray(wdt*hgt/2), open_y = CreateArray(wdt*hgt/2), n_open = 1;
	var i,x,y,x2,y2,xx,yy,v;
	// Close off some random ranges to make maze look more interesting
	for (i=0; i<6; ++i)
	{
		// random rectangle - can never close left or right border
		x = Random(wdt-2) + 1;
		y = Random(hgt-2) + 1;
		var szx = Random(20);
		var szy = Random(20-szx);
		x2 = Min(x+szx, wdt-2);
		y2 = Min(y+szy, hgt-2);
		for (yy=y; yy<y2; ++yy)
			for (xx=x; xx<x2; ++xx)
				visited[xx+yy*wdt] = -1;
	}
	// Generate pathes to all unvisited cells
	while (n_open)
	{
		// Pick a random open cell
		i = Random(n_open);
		x = open_x[i];
		y = open_y[i];
		// Remove cell from open list
		if (--n_open != i)
		{
			open_x[i] = open_x[n_open];
			open_y[i] = open_y[n_open];
		}
		// Already handled?
		if (visited[x+y*wdt]) continue;
		// Check neighbours
		var n_neighbour_found = 0, walk_dir, neighbour_visited = 0;
		for (var dir in directions)
		{
			var xn = x+dir[0], yn = y+dir[1];
			if (!Inside(xn,0,wdt-1) || !Inside(yn,0,hgt-1)) continue;
			v = visited[xn+yn*wdt];
			if (v<0)
			{
				// A blocked off neighbour. Ignore.
				continue;
			}
			else if (v)
			{
				// A visited neighbour: Might open a passage to this
				if (Random(++n_neighbour_found)) continue;
				walk_dir = dir;
				neighbour_visited = v;
			}
			else
			{
				// An unvisited neighbour: Add to open list
				open_x[n_open] = xn;
				open_y[n_open] = yn;
				++n_open;
			}
		}
		// Open passage to randomly selected visited neighbour
		if (walk_dir) // walk_dir is nil on first cell
			if (walk_dir[0])
				passages_x[x-(walk_dir[0]<0)+y*wdt] = true;
			else
				passages_y[x+(y-(walk_dir[1]<0))*wdt] = true;
		// Visit it!
		visited[x+y*wdt] = neighbour_visited + 1;
	}
	// Find exit point that is hard to reach
	var exit_moves = 0;
	for (y=0; y<hgt; ++y)
		if (visited[wdt-1+y*wdt] > exit_moves)
		{
			exit_y = y; exit_moves = visited[wdt-1+y*wdt];
		}
	// Draw map
	var pad_left = 10, pad_right = 10, pad_top = 0, pad_bottom = 0;
	var total_wdt = wdt*2+1+pad_left+pad_right, total_hgt = hgt*2+1+pad_top+pad_bottom;
	map->Resize(total_wdt, total_hgt);
	var bg_mat_name = "Sky";
	var front_mat_name = "BrickSoft-brick1"; // "DuroLava"
	var blocked_mat_name = "Water";
	map->Draw(bg_mat_name, nil, [0,0,1,1]);
	var bg_mat = map->GetPixel(0,0);
	map->Draw(blocked_mat_name, nil, [0,0,1,1]);
	var blocked_mat = map->GetPixel(0,0);
	map->Draw(front_mat_name);
	i=0;
	for (y = 0; y<hgt; ++y)
		for (x = 0; x<wdt; ++x)
		{
			xx = pad_left + 1 + x*2;
			yy = pad_top  + 1 + y*2;
			v = visited[x+y*wdt];
			if (v>=0)
			{
				// Passage pixel
				map->SetPixel(xx, yy, bg_mat);
				if (passages_x[i]) map->SetPixel(xx+1, yy, bg_mat);
				if (passages_y[i]) map->SetPixel(xx, yy+1, bg_mat);
			}
			else
			{
				// Blocked pixel. Fill with water!
				map->SetPixel(xx, yy, blocked_mat);
				// Extend to blocked neighbours
				if (visited[x+1+y*wdt] < 0) map->SetPixel(xx+1, yy, blocked_mat);
				if (visited[x+(y+1)*wdt] < 0) map->SetPixel(xx, yy+1, blocked_mat);
				if (visited[x+1+(y+1)*wdt] < 0) map->SetPixel(xx+1, yy+1, blocked_mat);
			}
			++i;
		}
	// Entry and exit
	entry_x = pad_left;
	entry_y = pad_top + 1 + sy*2;
	exit_x = pad_left+wdt*2;
	exit_y = pad_top+exit_y*2+1;
	map->SetPixel(entry_x, entry_y, bg_mat);
	map->SetPixel(exit_x, exit_y, bg_mat);
	entry_cave_x = entry_x-3;
	entry_cave_y = BoundBy(entry_y, 3, total_hgt-4);
	exit_cave_x = exit_x + 3;
	exit_cave_y = BoundBy(exit_y, 3, total_hgt-4);
	map->Draw(bg_mat_name, nil, [entry_cave_x-2,entry_cave_y-2,5,5]);
	map->Draw(bg_mat_name, nil, [exit_cave_x-2,exit_cave_y-2,5,5]);
	return true;
}
