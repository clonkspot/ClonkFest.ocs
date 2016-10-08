/*-- 
	Party game: Hot Ice
	Author: Sven2
	
	Melee on melting ice block with last man standing
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "HotIce"; }
func GetGameClonkMaxEnergy() { return 100; }
func GetGameStartPos(int player, int start_index, int max_index)
{
	var map_zoom = LandscapeWidth() / map_width;
	var pos = player_spawn_positions[start_index % GetLength(player_spawn_positions)];
	return {x=pos[0]*map_zoom, y=pos[1]*map_zoom};
}
func GetGameClonkMaxContents() { return 2; }

func IsGameLastManStanding() { return true; } // Game should end automatically if only one player is left alive

static Game_HotIce_MapIndex;
local player_spawn_positions, map_width; // change to static when editing in template

func InitFest()
{
	// First game on small islands map; next on big island
	Game_HotIce_MapIndex = 0;
	return _inherited(...);
}

// Return random order of numbers 0 to n-1
func GetRandomPermutation(int n)
{
	var r = CreateArray(n);
	for (var i=0; i<n; ++i) r[i] = i;
	for (var i=0; i<n; ++i)
	{
		var j = Random(n);
		if (i != j)
		{
			var v = r[j];
			r[j] = r[i];
			r[i] = v;
		}
	}
	return r;
}

func InitGame(array players)
{
	// Place players
	for (var player in players)
	{
		var clonk = GetCrew(player);
		if (clonk)
		{
			clonk->CreateContents(WindBag);
			var launcher = clonk->CreateContents(GrenadeLauncher);
			launcher->CreateContents(IronBomb);
			launcher->AddTimer(this.ReplenishLauncherAmmo, 10);
		}
	}
	// Place materials
	var i,pos;
	var ls_wdt = LandscapeWidth(), ls_hgt = LandscapeHeight();
	// Boom packs
	var num_extras = 12;
	for (i=0; i<num_extras; ++i)
		if (pos=FindLocation(Loc_InRect(0,0,ls_wdt,ls_hgt*3/4), Loc_Wall(CNAT_Bottom)))
			CreateObjectAbove(Boompack,pos.x,pos.y);
	// Materials: Firestones and iron bombs
	for (i=0; i<30; ++i)
		if (pos=FindLocation(Loc_InRect(0,0,ls_wdt,ls_hgt*3/4), Loc_Solid()))
			if (IsFirestoneSpot(pos.x,pos.y))
				CreateObjectAbove([Firestone,IronBomb][Random(Random(3))],pos.x,pos.y-1);
	// Player deactivation
	return inherited(players);
}

func IsFirestoneSpot(int x, int y)
{
// Very thorough ice surrounding check so they don't explode right away or when the first layer of ice melts
	return GBackSolid(x,y-1) && GBackSolid(x,y+4) && GBackSolid(x-2,y) && GBackSolid(x+2,y);
}

/* Called periodically in grenade launcher */
func ReplenishLauncherAmmo()
{
	if (!ContentsCount()) CreateContents(IronBomb);
	return true;
}


/* Map creation */

func InitializeMap(proplist map)
{
	// Map type 0: One big island; more small islands above
	// Map type 1: Only many small islands
	var t = (++Game_HotIce_MapIndex) % 2;
	var w = map.Wdt, h=map.Hgt;
	map_width = w;
	
	// Bottom lava lake
	map->Draw("^DuroLava", nil, [0,h*4/5,w,h/5]);
	
	if (t == 0) DrawBigIslandMap(map);
	if (t == 1) DrawSmallIslandsMap(map);
	
	// Alternate texctures
	var icealt_tex = { Algo=MAPALGO_RndChecker, Wdt=2, Hgt=3 };
	icealt_tex = { Algo=MAPALGO_Turbulence, Op=icealt_tex };
	icealt_tex = { Algo=MAPALGO_And, Op=[map->Duplicate("Ice"), icealt_tex]};
	map->Draw("^Ice-ice", icealt_tex);
	
	// Return true to tell the engine a map has been successfully created.
	return true;
}


func DrawBigIslandMap(proplist map)
{
	var w = map.Wdt, h=map.Hgt;
	// Draw one big island as the ground and some smaller islands floating above
	// Big
	var island = { Algo=MAPALGO_Polygon, X=[0,w,w*6/8,w*2/8], Y=[h*4/10,h*4/10,h*7/10,h*7/10] };
	island = { Algo=MAPALGO_Turbulence, Op=island, Amplitude=[0, 8] };
	map->Draw("^Ice-ice2", island, [w/10,h*13/20,w*8/10,h*3/20]); 
	// Make sure one row of inner island is drawn because it's used for player spawns
	map->Draw("^Ice-ice2", nil, [w*3/10,h*13/20,w*4/10+1,1]); 
	// Smaller floating
	var n_islands = 12;
	while(n_islands--)
	{
		var x = w*1/10 + Random(w*8/10);
		var y = h*2/10 + Random(h*3/10);
		map->Draw("^Ice-ice2", nil, [x,y,1,1]);
	}
	// Player spawns simply in middle of big island
	var plrcnt = Max(GetPlayerCount(C4PT_User), 2);
	player_spawn_positions = CreateArray(plrcnt);
	for (var i = 0; i < plrcnt; ++i)
	{
		player_spawn_positions[i] = [w*3/10 + i*w*4/10/(plrcnt-1), h*13/20];
	}
	return true;
}

func DrawSmallIslandsMap(proplist map)
{
	var w = map.Wdt, h=map.Hgt, x, y, szx, szy;
	// Islands in center of map
	var n_islands = 35;
	while(n_islands--)
	{
		y = h*3/10 + Random(h*5/10 - 3);
		var xrange = w * (y)/(h*9/10);
		x = w/2 - xrange/2 + Random(xrange);
		szx = Random(3);
		szy = 1;
		if (y > h/2) szy += Random(2); // lower islands sometimes taller
		if (Abs(x-w/2) < w/10) szx += Random(3); // central islands sometimes wider
		map->Draw("^Ice-ice2", nil, [x-szx,y,1+2*szx,szy]);
	}
	// Starting islands for player spawns
	var spawn_island_count = Max(GetPlayerCount(C4PT_User), 2);
	player_spawn_positions = CreateArray(spawn_island_count);
	for (var i = 0; i < spawn_island_count; ++i)
	{
		var x = w*2/10 + i * (w*6/10) / (spawn_island_count - 1);
		var y = Max(1, h/10) + Abs(x-w/2) * 3*h/10/w + 4;
		map->Draw("^Ice-ice2", nil, [x,y,1,1]);
		player_spawn_positions[i] = [x, y];
	}
	return true;
}
