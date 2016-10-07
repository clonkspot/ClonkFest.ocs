/*-- 
	Party game template
	Author: Sven2
	
	Another Clonk Fest game.
--*/

#include GameBase

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "ClickMe"; }
func GetGameTimeLimit() { return 150; }
func GetGameMinPlayers() { return 1; }
func GetGameMaxZoomRange() { return {x=LandscapeWidth(), y=LandscapeHeight()}; }
func GetGameViewLock() { return false; }
func GetGameStartPos(int player) { return {x=LandscapeWidth()/2-100, y=LandscapeHeight()/2}; }
func GetGameClonkMaxContents() { return 1; }

local num_remaining, scores;

func InitGame(array players)
{
	SetPosition(0,0);
	RemoveAll(Find_ID(ClickMe_Target));
	var n_max = GetLength(Quests);
	var n_place = num_remaining = 10;
	while (n_place)
	{
		var q = Quests[Random(n_max)];
		// avoid duplicate targets at same place
		if (FindObject(Find_ID(ClickMe_Target), Find_AtRect(q.x-20,q.y-20,40,40))) continue;
		PlaceQuest(q);
		--n_place;
	}
	Scoreboard->Init([{key = "game", title = Format("{{Wipf}}/%d", num_remaining), sorted = true, desc = true, default = "0", priority = 100}]);
	scores = [];
	for (var plr in players)
	{
		scores[plr] = 0;
		Scoreboard->SetPlayerData(plr, "game", 0);
		var crew = GetCrew(plr);
		crew->SetCategory(1);
		crew.Visibility = VIS_None;
	}
	return true;
}

func StartGame(array players)
{
	for (var plr in players)
	{
		var crew = GetCrew(plr);
		var pointer = crew->CreateContents(ClickMe_Pointer);
		pointer->SetGameObject(this);
	}
	return true;
}

// Callback function when game is finished
func OnGameFinished()
{
	// Clear remaining Wipfs
	for (var obj in FindObjects(Find_ID(ClickMe_Target), Find_Func("IsValidTarget")))
		obj->OnFound();
	// Determine winners
	var max_score = GetMaxScore();
	var winners = [];
	for (var plr in GetGamePlayers())
	{
		var score = scores[plr];
		if (score >= max_score) winners[GetLength(winners)] = plr;
	}
	SetGameWinners(winners);
	return 1;
}

func InitFest() { return true;}

local Name = "$Name$";
local Description = "$Description$";

func OnClickMe(int plr, int x, int y)
{
	var target = FindObject(Find_ID(ClickMe_Target), Find_AtPoint(x-GetX(),y-GetY()), Find_Func("IsValidTarget"));
	if (target)
	{
		Sound("UI::Cash", true, 100);
		++scores[plr];
		Scoreboard->SetPlayerData(plr, "game", scores[plr]);
		target->OnFound(); // mark invalid and fade out
		--num_remaining;
		var plr_score = scores[plr];
		var max_score = GetMaxScore();
		var any_chance;
		for (var other_plr in GetGamePlayers()) if (plr != other_plr) if (scores[other_plr] + num_remaining >= plr_score) any_chance = true;
		if (!any_chance || !num_remaining) FinishGame();
		return true;
	}
	else
	{
		Sound("UI::Error", true, 100, plr);
		return false;
	}
}

func GetMaxScore()
{
	var max_score = 0;
	for (var plr in GetGamePlayers()) max_score = Max(max_score, scores[plr]);
	return max_score;
}



// Helper function

func PlaceQuest(proplist q)
{
	var obj = CreateObject(ClickMe_Target,0,0,NO_OWNER);
	if (obj) obj->SetData(q);
	return obj;
}


/*-- Proplist --*/

local Quests;

func Definition()
{
	var data = CreateArray(361);
	data[0]={action="Wipf",x=261,y=105,clrmod=0x80b0b080,scale=35,plane=500,dir=1,};
	data[1]={action="Wipf",x=792,y=598,clrmod=0x80b0b080,scale=13,plane=500,dir=1,};
	data[2]={action="Wipf",x=710,y=664,clrmod=0x80b0b080,scale=12,plane=500,r=162,dir=1,};
	data[3]={action="Wipf",x=737,y=542,clrmod=0x80b0b080,scale=15,plane=500,dir=1,};
	data[4]={action="Wipf",x=485,y=85,clrmod=0x80b0b080,scale=44,plane=500,};
	data[5]={action="Wipf",x=539,y=429,clrmod=0x80b0b080,scale=57,plane=500,r=49,};
	data[6]={action="Wipf",x=549,y=452,clrmod=0x80b0b080,scale=11,plane=500,r=-32,dir=1,};
	data[7]={action="Wipf",x=281,y=98,clrmod=0x80b0b080,scale=47,plane=500,r=11,dir=1,};
	data[8]={action="Wipf",x=190,y=481,clrmod=0x80b0b080,scale=43,plane=500,dir=1,};
	data[9]={action="Wipf",x=653,y=472,clrmod=0x80b0b080,scale=22,plane=500,dir=1,};
	data[10]={action="Wipf",x=1117,y=429,clrmod=0x80b0b080,scale=10,plane=500,r=130,};
	data[11]={action="Wipf",x=332,y=98,clrmod=0x80b0b080,scale=37,plane=500,dir=1,};
	data[12]={action="Wipf",x=588,y=606,clrmod=0x80b0b080,scale=58,plane=500,dir=1,};
	data[13]={action="Wipf",x=125,y=540,clrmod=0x80b0b080,scale=38,plane=500,dir=1,};
	data[14]={action="Wipf",x=863,y=76,clrmod=0x80b0b080,scale=25,plane=500,dir=1,};
	data[15]={action="Wipf",x=316,y=310,clrmod=0x80b0b080,scale=22,plane=500,dir=1,};
	data[16]={action="Wipf",x=43,y=198,clrmod=0x80b0b080,scale=46,plane=500,r=154,dir=1,};
	data[17]={action="Wipf",x=365,y=238,clrmod=0x80b0b080,scale=10,plane=500,r=-35,dir=1,};
	data[18]={action="Wipf",x=555,y=711,clrmod=0x80b0b080,scale=50,plane=500,dir=1,};
	data[19]={action="Wipf",x=568,y=458,clrmod=0x80b0b080,scale=55,plane=500,dir=1,};
	data[20]={action="Wipf",x=542,y=440,clrmod=0x80b0b080,scale=24,plane=500,r=34,dir=1,};
	data[21]={action="Wipf",x=892,y=643,clrmod=0x80b0b080,scale=36,plane=500,dir=1,};
	data[22]={action="Wipf",x=160,y=224,clrmod=0x80b0b080,scale=34,plane=500,r=-68,dir=1,};
	data[23]={action="Wipf",x=313,y=410,clrmod=0x80b0b080,scale=28,plane=500,r=-7,dir=1,};
	data[24]={action="Wipf",x=651,y=448,clrmod=0x80b0b080,scale=42,plane=500,dir=1,};
	data[25]={action="Wipf",x=429,y=645,clrmod=0x80b0b080,scale=46,plane=500,};
	data[26]={action="Wipf",x=822,y=100,clrmod=0x80b0b080,scale=34,plane=500,dir=1,};
	data[27]={action="Wipf",x=354,y=178,clrmod=0x80b0b080,scale=43,plane=500,r=111,dir=1,};
	data[28]={action="Wipf",x=173,y=216,clrmod=0x80b0b080,scale=45,plane=500,dir=1,};
	data[29]={action="Wipf",x=359,y=279,clrmod=0x80b0b080,scale=26,plane=500,dir=1,};
	data[30]={action="Wipf",x=367,y=284,clrmod=0x80b0b080,scale=14,plane=500,};
	data[31]={action="Wipf",x=849,y=612,clrmod=0x80b0b080,scale=24,plane=500,dir=1,};
	data[32]={action="Wipf",x=471,y=182,clrmod=0x80b0b080,scale=46,plane=500,r=-98,dir=1,};
	data[33]={action="Wipf",x=600,y=419,clrmod=0x80b0b080,scale=24,plane=500,};
	data[34]={action="Wipf",x=833,y=63,clrmod=0x80b0b080,scale=13,plane=500,};
	data[35]={action="Wipf",x=463,y=113,clrmod=0x80b0b080,scale=31,plane=500,r=-154,dir=1,};
	data[36]={action="Wipf",x=1006,y=129,clrmod=0x80b0b080,scale=38,plane=500,dir=1,};
	data[37]={action="Wipf",x=816,y=593,clrmod=0x80b0b080,scale=59,plane=500,r=128,dir=1,};
	data[38]={action="Wipf",x=611,y=382,clrmod=0x80b0b080,scale=15,plane=500,r=-163,dir=1,};
	data[39]={action="Wipf",x=469,y=425,clrmod=0x80b0b080,scale=10,plane=500,dir=1,};
	data[40]={action="Wipf",x=221,y=338,clrmod=0x80b0b080,scale=45,plane=500,dir=1,};
	data[41]={action="Wipf",x=543,y=445,clrmod=0x80b0b080,scale=27,plane=500,r=151,dir=1,};
	data[42]={action="Wipf",x=761,y=637,clrmod=0x80b0b080,scale=54,plane=500,r=-58,dir=1,};
	data[43]={action="Wipf",x=718,y=203,clrmod=0x80b0b080,scale=48,plane=500,dir=1,};
	data[44]={action="Wipf",x=679,y=205,clrmod=0x80b0b080,scale=41,plane=500,dir=1,};
	data[45]={action="Wipf",x=657,y=421,clrmod=0x80b0b080,scale=34,plane=500,dir=1,};
	data[46]={action="Wipf",x=415,y=441,clrmod=0x80b0b080,scale=41,plane=500,r=-34,};
	data[47]={action="Wipf",x=667,y=430,clrmod=0x80b0b080,scale=49,plane=500,r=79,};
	data[48]={action="Wipf",x=563,y=407,clrmod=0x80b0b080,scale=55,plane=500,};
	data[49]={action="Wipf",x=426,y=29,clrmod=0x80b0b080,scale=20,plane=500,r=89,dir=1,};
	data[50]={action="Wipf",x=187,y=521,clrmod=0x80b0b080,scale=53,plane=500,};
	data[51]={action="Wipf",x=285,y=694,clrmod=0x80b0b080,scale=48,plane=500,dir=1,};
	data[52]={action="Wipf",x=800,y=102,clrmod=0x80b0b080,scale=37,plane=500,dir=1,};
	data[53]={action="Wipf",x=835,y=610,clrmod=0x80b0b080,scale=22,plane=500,r=-30,dir=1,};
	data[54]={action="Wipf",x=236,y=692,clrmod=0x80b0b080,scale=16,plane=500,r=-67,dir=1,};
	data[55]={action="Wipf",x=205,y=449,clrmod=0x80b0b080,scale=59,plane=500,r=110,dir=1,};
	data[56]={action="Wipf",x=245,y=367,clrmod=0x80b0b080,scale=44,plane=500,dir=1,};
	data[57]={action="Wipf",x=438,y=423,clrmod=0x80b0b080,scale=19,plane=500,dir=1,};
	data[58]={action="Wipf",x=573,y=500,clrmod=0x80b0b080,scale=36,plane=500,r=118,dir=1,};
	data[59]={action="Wipf",x=254,y=89,clrmod=0x80b0b080,scale=35,plane=500,r=25,};
	data[60]={action="Wipf",x=208,y=141,clrmod=0x80b0b080,scale=36,plane=500,dir=1,};
	data[61]={action="Wipf",x=584,y=428,clrmod=0x80b0b080,scale=36,plane=500,};
	data[62]={action="Wipf",x=596,y=208,clrmod=0x80b0b080,scale=44,plane=500,r=-52,dir=1,};
	data[63]={action="Wipf",x=832,y=635,clrmod=0x80b0b080,scale=11,plane=500,r=-48,dir=1,};
	data[64]={action="Wipf",x=370,y=310,clrmod=0x80b0b080,scale=36,plane=500,r=173,dir=1,};
	data[65]={action="Wipf",x=726,y=704,clrmod=0x80b0b080,scale=16,plane=500,dir=1,};
	data[66]={action="Wipf",x=645,y=457,clrmod=0x80b0b080,scale=44,plane=500,dir=1,};
	data[67]={action="Wipf",x=745,y=558,clrmod=0x80b0b080,scale=22,plane=500,r=139,dir=1,};
	data[68]={action="Wipf",x=933,y=120,clrmod=0x80b0b080,scale=47,plane=500,r=121,};
	data[69]={action="Wipf",x=1110,y=233,clrmod=0x80b0b080,scale=46,plane=500,r=60,dir=1,};
	data[70]={action="Wipf",x=303,y=337,clrmod=0x80b0b080,scale=50,plane=500,r=5,dir=1,};
	data[71]={action="Wipf",x=266,y=678,clrmod=0x80b0b080,scale=58,plane=500,dir=1,};
	data[72]={action="Wipf",x=624,y=372,clrmod=0x80b0b080,scale=18,plane=500,r=152,dir=1,};
	data[73]={action="Wipf",x=494,y=67,clrmod=0x80b0b080,scale=18,plane=500,dir=1,};
	data[74]={action="Wipf",x=627,y=424,clrmod=0x80b0b080,scale=13,plane=500,dir=1,};
	data[75]={action="Wipf",x=652,y=471,clrmod=0x80b0b080,scale=15,plane=500,dir=1,};
	data[76]={action="Wipf",x=257,y=339,clrmod=0x80b0b080,scale=55,plane=500,r=-23,};
	data[77]={action="Wipf",x=108,y=533,clrmod=0x80b0b080,scale=38,plane=500,r=-45,dir=1,};
	data[78]={action="Wipf",x=499,y=458,clrmod=0x80b0b080,scale=48,plane=500,dir=1,};
	data[79]={action="Wipf",x=638,y=621,clrmod=0x80b0b080,scale=57,plane=500,dir=1,};
	data[80]={action="Wipf",x=907,y=638,clrmod=0x80b0b080,scale=15,plane=500,r=-135,dir=1,};
	data[81]={action="Wipf",x=431,y=432,clrmod=0x80b0b080,scale=20,plane=500,r=-56,dir=1,};
	data[82]={action="Wipf",x=177,y=125,clrmod=0x80b0b080,scale=55,plane=500,dir=1,};
	data[83]={action="Wipf",x=145,y=397,clrmod=0x80b0b080,scale=59,plane=500,dir=1,};
	data[84]={action="Wipf",x=791,y=199,clrmod=0x80b0b080,scale=27,plane=500,r=73,dir=1,};
	data[85]={action="Wipf",x=580,y=418,clrmod=0x80b0b080,scale=34,plane=500,dir=1,};
	data[86]={action="Wipf",x=321,y=464,clrmod=0x80b0b080,scale=50,plane=500,dir=1,};
	data[87]={action="Wipf",x=296,y=279,clrmod=0x80b0b080,scale=48,plane=500,r=62,dir=1,};
	data[88]={action="Wipf",x=287,y=310,clrmod=0x80b0b080,scale=18,plane=500,r=-2,dir=1,};
	data[89]={action="Wipf",x=244,y=128,clrmod=0x80b0b080,scale=30,plane=500,};
	data[90]={action="Wipf",x=978,y=651,clrmod=0x80b0b080,scale=19,plane=500,r=108,dir=1,};
	data[91]={action="Wipf",x=692,y=540,clrmod=0x80b0b080,scale=19,plane=500,dir=1,};
	data[92]={action="Wipf",x=928,y=647,clrmod=0x80b0b080,scale=14,plane=500,r=166,dir=1,};
	data[93]={action="Wipf",x=344,y=338,clrmod=0x80b0b080,scale=47,plane=500,dir=1,};
	data[94]={action="Wipf",x=211,y=407,clrmod=0x20ffffff,scale=200,r=-90,dir=1,};
	data[95]={action="Wipf",x=826,y=80,clrmod=0x10ffffff,scale=200,dir=1,};
	data[96]={action="Wipf",x=457,y=78,clrmod=0x10ffffff,scale=200,dir=1,};
	data[97]={action="Wipf",x=653,y=495,clrmod=0x10ffffff,scale=200,r=90,dir=1,};
	data[98]={action="Wipf",x=985,y=689,clrmod=0x20000000,blitmode=130,};
	data[99]={action="Wipf",x=183,y=328,dir=1,};
	data[100]={action="Wipf",x=684,y=608,clrmod=0x80808080,scale=114,r=-158,dir=1,};
	data[101]={action="Wipf",x=867,y=136,clrmod=0x80808080,scale=84,dir=1,};
	data[102]={action="Wipf",x=296,y=556,clrmod=0x808080ff,scale=85,dir=1,};
	data[103]={action="Wipf",x=906,y=252,clrmod=0x808080ff,scale=95,r=157,};
	data[104]={action="Wipf",x=833,y=615,scale=44,r=-52,dir=1,};
	data[105]={action="Wipf",x=723,y=735,clrmod=0x80808080,scale=99,};
	data[106]={action="Wipf",x=891,y=156,clrmod=0x808080ff,scale=82,dir=1,};
	data[107]={action="Wipf",x=1020,y=178,clrmod=0x80808080,scale=70,r=93,dir=1,};
	data[108]={action="Wipf",x=464,y=183,clrmod=0x808080ff,scale=111,r=-162,dir=1,};
	data[109]={action="Wipf",x=786,y=212,clrmod=0x80808080,scale=34,r=83,dir=1,};
	data[110]={action="Wipf",x=1088,y=268,clrmod=0x80808080,scale=106,r=106,};
	data[111]={action="Wipf",x=418,y=486,clrmod=0x808080ff,scale=50,r=-120,};
	data[112]={action="Wipf",x=523,y=182,clrmod=0x808080ff,scale=108,r=-157,dir=1,};
	data[113]={action="Wipf",x=314,y=403,clrmod=0x80808080,scale=80,dir=1,};
	data[114]={action="Wipf",x=334,y=530,scale=51,dir=1,};
	data[115]={action="Wipf",x=189,y=268,scale=69,r=147,dir=1,};
	data[116]={action="Wipf",x=363,y=468,clrmod=0x808080ff,scale=28,r=91,};
	data[117]={action="Wipf",x=360,y=539,clrmod=0x808080ff,scale=102,r=73,};
	data[118]={action="Wipf",x=994,y=262,clrmod=0x80808080,scale=26,dir=1,};
	data[119]={action="Wipf",x=593,y=726,clrmod=0x80808080,scale=34,r=-158,dir=1,};
	data[120]={action="Wipf",x=233,y=141,clrmod=0x80808080,scale=56,dir=1,};
	data[121]={action="Wipf",x=347,y=74,clrmod=0x808080ff,scale=108,r=-92,dir=1,};
	data[122]={action="Wipf",x=724,y=542,clrmod=0x808080ff,scale=21,dir=1,};
	data[123]={action="Wipf",x=732,y=626,clrmod=0x80808080,scale=96,};
	data[124]={action="Wipf",x=847,y=125,scale=51,};
	data[125]={action="Wipf",x=78,y=383,clrmod=0x808080ff,scale=103,r=89,dir=1,};
	data[126]={action="Wipf",x=285,y=547,clrmod=0x808080ff,scale=93,r=89,};
	data[127]={action="Wipf",x=527,y=695,clrmod=0x80808080,scale=71,dir=1,};
	data[128]={action="Wipf",x=38,y=156,clrmod=0x808080ff,scale=38,dir=1,};
	data[129]={action="Wipf",x=721,y=198,clrmod=0x808080ff,scale=70,dir=1,};
	data[130]={action="Wipf",x=717,y=246,clrmod=0x80808080,scale=42,r=-143,dir=1,};
	data[131]={action="Wipf",x=246,y=488,clrmod=0x808080ff,scale=110,r=-54,dir=1,};
	data[132]={action="Wipf",x=513,y=734,clrmod=0x80808080,scale=113,dir=1,};
	data[133]={action="Wipf",x=1096,y=714,clrmod=0x80808080,scale=60,};
	data[134]={action="Wipf",x=315,y=514,scale=54,r=-173,dir=1,};
	data[135]={action="Wipf",x=193,y=428,clrmod=0x808080ff,scale=50,};
	data[136]={action="Wipf",x=192,y=227,clrmod=0x808080ff,scale=78,dir=1,};
	data[137]={action="Wipf",x=561,y=490,clrmod=0x80808080,scale=27,dir=1,};
	data[138]={action="Wipf",x=320,y=482,clrmod=0x80808080,scale=56,dir=1,};
	data[139]={action="Wipf",x=100,y=311,clrmod=0x808080ff,scale=108,dir=1,};
	data[140]={action="Wipf",x=329,y=123,clrmod=0x80808080,scale=90,dir=1,};
	data[141]={action="Wipf",x=810,y=121,clrmod=0x808080ff,scale=22,dir=1,};
	data[142]={action="Wipf",x=375,y=128,clrmod=0x808080ff,scale=27,dir=1,};
	data[143]={action="Wipf",x=477,y=127,clrmod=0x808080ff,scale=85,r=162,dir=1,};
	data[144]={action="Wipf",x=399,y=117,clrmod=0x808080ff,scale=42,r=-5,};
	data[145]={action="Wipf",x=161,y=433,clrmod=0x80808080,scale=102,};
	data[146]={action="Wipf",x=33,y=429,clrmod=0x808080ff,scale=93,dir=1,};
	data[147]={action="Wipf",x=189,y=727,clrmod=0x80808080,scale=45,r=46,dir=1,};
	data[148]={action="Wipf",x=136,y=169,clrmod=0x808080ff,scale=112,r=-91,dir=1,};
	data[149]={action="Wipf",x=856,y=606,clrmod=0x808080ff,scale=60,dir=1,};
	data[150]={action="Wipf",x=535,y=543,clrmod=0x808080ff,scale=61,r=-143,};
	data[151]={action="Wipf",x=958,y=716,clrmod=0x80808080,scale=78,r=-112,};
	data[152]={action="Wipf",x=292,y=629,clrmod=0x80808080,scale=102,dir=1,};
	data[153]={action="Wipf",x=382,y=598,clrmod=0x808080ff,scale=73,dir=1,};
	data[154]={action="Wipf",x=333,y=208,clrmod=0x80808080,scale=23,r=-88,dir=1,};
	data[155]={action="Wipf",x=758,y=163,scale=115,};
	data[156]={action="Wipf",x=613,y=646,clrmod=0x80808080,scale=30,};
	data[157]={action="Wipf",x=214,y=158,clrmod=0x808080ff,scale=54,dir=1,};
	data[158]={action="Wipf",x=356,y=712,clrmod=0x808080ff,scale=105,dir=1,};
	data[159]={action="Wipf",x=285,y=373,clrmod=0x80808080,scale=69,r=-134,dir=1,};
	data[160]={action="Wipf",x=572,y=560,clrmod=0x808080ff,scale=84,dir=1,};
	data[161]={action="Wipf",x=414,y=598,clrmod=0x80808080,scale=109,dir=1,};
	data[162]={action="Wipf",x=143,y=478,clrmod=0x80808080,scale=86,r=148,};
	data[163]={action="Wipf",x=699,y=727,scale=78,dir=1,};
	data[164]={action="Wipf",x=640,y=527,scale=76,r=132,dir=1,};
	data[165]={action="Wipf",x=629,y=214,clrmod=0x808080ff,scale=45,r=-163,dir=1,};
	data[166]={action="Wipf",x=559,y=588,clrmod=0x80808080,scale=110,};
	data[167]={action="Wipf",x=103,y=8,clrmod=0x80808080,scale=65,r=-177,};
	data[168]={action="Wipf",x=934,y=194,clrmod=0xff404040,scale=64,blitmode=129,dir=1,};
	data[169]={action="Wipf",x=805,y=709,clrmod=0xff404040,scale=60,blitmode=129,r=-138,dir=1,};
	data[170]={action="Wipf",x=661,y=248,clrmod=0xff404040,scale=50,blitmode=129,r=175,dir=1,};
	data[171]={action="Wipf",x=470,y=546,clrmod=0x80808080,scale=102,r=-58,dir=1,};
	data[172]={action="Wipf",x=77,y=690,clrmod=0x808080ff,scale=75,r=-21,dir=1,};
	data[173]={action="Wipf",x=878,y=618,scale=111,r=55,dir=1,};
	data[174]={action="Wipf",x=446,y=81,scale=89,r=22,};
	data[175]={action="Wipf",x=362,y=285,scale=27,r=-131,};
	data[176]={action="Wipf",x=606,y=418,clrmod=0xff404040,scale=83,blitmode=129,r=-28,};
	data[177]={action="Wipf",x=378,y=352,scale=82,r=84,dir=1,};
	data[178]={action="Wipf",x=650,y=488,scale=69,r=160,};
	data[179]={action="Wipf",x=210,y=589,clrmod=0x80808080,scale=84,r=63,};
	data[180]={action="Wipf",x=559,y=33,clrmod=0x80808080,scale=87,r=13,};
	data[181]={action="Wipf",x=543,y=91,clrmod=0x80808080,scale=42,r=47,dir=1,};
	data[182]={action="Wipf",x=297,y=444,clrmod=0x808080ff,scale=29,};
	data[183]={action="Wipf",x=143,y=194,clrmod=0x80808080,scale=99,r=-122,};
	data[184]={action="Wipf",x=903,y=201,scale=22,r=167,dir=1,};
	data[185]={action="Wipf",x=261,y=366,scale=26,};
	data[186]={action="Wipf",x=505,y=614,clrmod=0x808080ff,scale=74,};
	data[187]={action="Wipf",x=105,y=448,clrmod=0x808080ff,scale=93,dir=1,};
	data[188]={action="Wipf",x=805,y=654,clrmod=0x80808080,scale=34,dir=1,};
	data[189]={action="Wipf",x=423,y=524,clrmod=0x80808080,scale=67,r=-12,};
	data[190]={action="Wipf",x=1080,y=203,clrmod=0x80808080,scale=74,r=-10,};
	data[191]={action="Wipf",x=53,y=162,clrmod=0x80808080,scale=39,r=55,};
	data[192]={action="Wipf",x=385,y=559,scale=54,r=39,dir=1,};
	data[193]={action="Wipf",x=635,y=411,scale=118,r=-12,};
	data[194]={action="Wipf",x=970,y=261,scale=91,r=-70,};
	data[195]={action="Wipf",x=787,y=97,scale=50,dir=1,};
	data[196]={action="Wipf",x=522,y=559,clrmod=0x80808080,scale=68,r=99,};
	data[197]={action="Wipf",x=1036,y=228,clrmod=0xff404040,scale=107,blitmode=129,r=98,dir=1,};
	data[198]={action="Wipf",x=519,y=94,clrmod=0x80808080,scale=109,r=-45,dir=1,};
	data[199]={action="Wipf",x=430,y=118,clrmod=0xff404040,scale=99,blitmode=129,dir=1,};
	data[200]={action="Wipf",x=991,y=152,clrmod=0xff404040,scale=104,blitmode=129,r=146,};
	data[201]={action="Wipf",x=359,y=42,clrmod=0x80808080,scale=118,r=-76,};
	data[202]={action="Wipf",x=622,y=597,clrmod=0x808080ff,scale=101,};
	data[203]={action="Wipf",x=580,y=506,clrmod=0x80808080,scale=105,r=175,dir=1,};
	data[204]={action="Wipf",x=847,y=72,clrmod=0x80808080,scale=108,};
	data[205]={action="Wipf",x=861,y=99,clrmod=0x80808080,scale=117,r=137,};
	data[206]={action="Wipf",x=22,y=111,clrmod=0x80808080,scale=73,};
	data[207]={action="Wipf",x=635,y=409,clrmod=0x80808080,scale=25,r=116,};
	data[208]={action="Wipf",x=149,y=242,scale=84,r=-56,dir=1,};
	data[209]={action="Wipf",x=1174,y=687,clrmod=0x80808080,scale=48,r=27,};
	data[210]={action="Wipf",x=642,y=680,clrmod=0x80808080,scale=66,};
	data[211]={action="Wipf",x=234,y=577,clrmod=0x80808080,scale=45,};
	data[212]={action="Wipf",x=102,y=535,clrmod=0x80808080,scale=58,r=-18,};
	data[213]={action="Wipf",x=1132,y=710,clrmod=0x80808080,scale=92,};
	data[214]={action="Wipf",x=298,y=323,clrmod=0x808080ff,scale=116,dir=1,};
	data[215]={action="Wipf",x=432,y=51,clrmod=0x808080ff,scale=69,r=70,dir=1,};
	data[216]={action="Wipf",x=164,y=332,clrmod=0x80808080,scale=79,r=-11,};
	data[217]={action="Wipf",x=893,y=661,clrmod=0x808080ff,scale=98,r=166,dir=1,};
	data[218]={action="Wipf",x=13,y=160,clrmod=0x80808080,scale=38,r=-61,dir=1,};
	data[219]={action="Wipf",x=361,y=371,clrmod=0x808080ff,scale=70,r=144,dir=1,};
	data[220]={action="Wipf",x=345,y=435,clrmod=0x808080ff,scale=82,dir=1,};
	data[221]={action="Wipf",x=555,y=102,clrmod=0x808080ff,scale=81,dir=1,};
	data[222]={action="Wipf",x=799,y=195,clrmod=0x80808080,scale=119,r=75,dir=1,};
	data[223]={action="Wipf",x=188,y=674,clrmod=0x80808080,scale=105,r=168,};
	data[224]={action="Wipf",x=187,y=613,clrmod=0x80808080,scale=77,r=-125,};
	data[225]={action="Wipf",x=217,y=315,clrmod=0x80808080,scale=20,r=-145,};
	data[226]={action="Wipf",x=63,y=186,clrmod=0x80808080,scale=112,r=116,dir=1,};
	data[227]={action="Wipf",x=588,y=698,scale=55,dir=1,};
	data[228]={action="Wipf",x=295,y=115,scale=47,};
	data[229]={action="Wipf",x=202,y=710,scale=75,dir=1,};
	data[230]={action="Wipf",x=835,y=125,clrmod=0x80808080,scale=72,r=-24,};
	data[231]={action="Wipf",x=723,y=220,clrmod=0x808080ff,scale=62,r=19,};
	data[232]={action="Wipf",x=510,y=145,clrmod=0xff404040,scale=27,blitmode=129,r=-35,dir=1,};
	data[233]={action="Wipf",x=427,y=39,clrmod=0x80808080,scale=65,};
	data[234]={action="Wipf",x=493,y=142,clrmod=0x80808080,scale=62,dir=1,};
	data[235]={action="Wipf",x=370,y=278,clrmod=0x80808080,scale=61,dir=1,};
	data[236]={action="Wipf",x=808,y=75,clrmod=0xff404040,scale=50,blitmode=129,};
	data[237]={action="Wipf",x=984,y=96,clrmod=0xff404040,scale=95,blitmode=129,};
	data[238]={action="Wipf",x=814,y=629,clrmod=0x80808080,scale=103,dir=1,};
	data[239]={action="Wipf",x=811,y=108,clrmod=0xff404040,scale=76,blitmode=129,r=160,dir=1,};
	data[240]={action="Wipf",x=580,y=716,clrmod=0x80808080,scale=96,};
	data[241]={action="Wipf",x=462,y=127,clrmod=0x808080ff,scale=24,r=93,dir=1,};
	data[242]={action="Wipf",x=354,y=548,clrmod=0x80808080,scale=40,r=48,};
	data[243]={action="Wipf",x=785,y=222,scale=29,r=175,};
	data[244]={action="Wipf",x=326,y=307,scale=60,};
	data[245]={action="Wipf",x=471,y=125,clrmod=0x80808080,scale=61,};
	data[246]={action="Wipf",x=507,y=177,clrmod=0x80808080,scale=76,r=106,};
	data[247]={action="Wipf",x=731,y=233,clrmod=0x80808080,scale=34,r=-138,};
	data[248]={action="Wipf",x=675,y=679,clrmod=0x808080ff,scale=56,dir=1,};
	data[249]={action="Wipf",x=617,y=395,clrmod=0x80808080,scale=63,r=103,dir=1,};
	data[250]={action="Wipf",x=858,y=127,clrmod=0x808080ff,scale=79,dir=1,};
	data[251]={action="Wipf",x=372,y=126,clrmod=0x808080ff,scale=42,dir=1,};
	data[252]={action="Wipf",x=384,y=175,clrmod=0x808080ff,scale=65,r=152,dir=1,};
	data[253]={action="Wipf",x=452,y=533,clrmod=0x80808080,scale=48,};
	data[254]={action="Wipf",x=409,y=472,clrmod=0x80808080,scale=103,r=-80,};
	data[255]={action="Wipf",x=350,y=377,clrmod=0x808080ff,scale=32,r=148,};
	data[256]={action="Wipf",x=36,y=211,clrmod=0x80808080,scale=35,};
	data[257]={action="Wipf",x=908,y=205,clrmod=0x808080ff,scale=68,r=-109,dir=1,};
	data[258]={action="Wipf",x=562,y=516,clrmod=0x808080ff,scale=80,r=103,dir=1,};
	data[259]={action="Wipf",x=487,y=57,clrmod=0x80808080,scale=27,};
	data[260]={action="Wipf",x=432,y=6,clrmod=0x80808080,scale=79,r=20,};
	data[261]={action="Wipf",x=781,y=622,clrmod=0x80808080,scale=41,r=-40,};
	data[262]={action="Wipf",x=197,y=270,clrmod=0x80808080,scale=77,r=137,};
	data[263]={action="Wipf",x=487,y=418,clrmod=0x80808080,scale=62,};
	data[264]={action="Wipf",x=1190,y=699,scale=71,dir=1,};
	data[265]={action="Wipf",x=800,y=82,clrmod=0x80808080,scale=26,r=-100,};
	data[266]={action="Wipf",x=525,y=407,clrmod=0x80808080,scale=31,};
	data[267]={action="Wipf",x=66,y=244,clrmod=0x80808080,scale=46,r=104,};
	data[268]={action="Wipf",x=900,y=177,clrmod=0x808080ff,scale=91,};
	data[269]={action="Wipf",x=445,y=672,clrmod=0x80808080,scale=91,dir=1,};
	data[270]={action="Wipf",x=739,y=590,clrmod=0x808080ff,scale=96,dir=1,};
	data[271]={action="Wipf",x=644,y=204,clrmod=0x80808080,scale=55,r=-29,};
	data[272]={action="Wipf",x=877,y=640,clrmod=0xff404040,scale=32,blitmode=129,r=106,dir=1,};
	data[273]={action="Wipf",x=260,y=195,clrmod=0xff404040,scale=116,blitmode=129,r=123,dir=1,};
	data[274]={action="Wipf",x=235,y=697,clrmod=0xff404040,scale=86,blitmode=129,dir=1,};
	data[275]={action="Wipf",x=1008,y=103,clrmod=0xff404040,scale=60,blitmode=129,dir=1,};
	data[276]={action="Wipf",x=1009,y=692,clrmod=0xff404040,scale=52,blitmode=129,r=-140,};
	data[277]={action="Wipf",x=239,y=513,clrmod=0x80808080,scale=84,};
	data[278]={action="Wipf",x=742,y=679,clrmod=0xff404040,scale=105,blitmode=129,r=-171,dir=1,};
	data[279]={action="Wipf",x=401,y=435,scale=99,};
	data[280]={action="Wipf",x=174,y=681,scale=83,dir=1,};
	data[281]={action="Wipf",x=54,y=229,clrmod=0xff404040,scale=54,blitmode=129,};
	data[282]={action="Wipf",x=344,y=649,scale=69,dir=1,};
	data[283]={action="Wipf",x=326,y=646,clrmod=0x80808080,scale=88,r=58,};
	data[284]={action="Wipf",x=431,y=450,clrmod=0x80808080,scale=89,};
	data[285]={action="Wipf",x=341,y=308,clrmod=0x80808080,scale=62,r=-75,};
	data[286]={action="Wipf",x=654,y=616,clrmod=0x80808080,scale=65,r=-24,dir=1,};
	data[287]={action="Wipf",x=952,y=692,clrmod=0x80808080,scale=113,dir=1,};
	data[288]={action="Wipf",x=948,y=163,clrmod=0x808080ff,scale=86,dir=1,};
	data[289]={action="Wipf",x=603,y=453,clrmod=0x80808080,scale=69,dir=1,};
	data[290]={action="Wipf",x=438,y=159,scale=38,r=125,};
	data[291]={action="Wipf",x=942,y=212,clrmod=0xff404040,scale=96,blitmode=129,r=-154,};
	data[292]={action="Wipf",x=400,y=125,clrmod=0x80808080,scale=74,r=-143,};
	data[293]={action="Wipf",x=700,y=196,clrmod=0x80808080,scale=83,dir=1,};
	data[294]={action="Wipf",x=973,y=116,clrmod=0x80808080,scale=80,};
	data[295]={action="Wipf",x=628,y=367,clrmod=0xff404040,scale=21,blitmode=129,r=147,dir=1,};
	data[296]={action="Wipf",x=469,y=434,clrmod=0x808080ff,scale=96,};
	data[297]={action="Wipf",x=536,y=632,clrmod=0x808080ff,scale=77,};
	data[298]={action="Wipf",x=634,y=350,clrmod=0x80808080,scale=28,};
	data[299]={action="Wipf",x=498,y=549,scale=27,};
	data[300]={action="Wipf",x=351,y=98,scale=48,r=-124,};
	data[301]={action="Wipf",x=454,y=422,scale=23,};
	data[302]={action="Wipf",x=247,y=408,clrmod=0xff404040,scale=86,blitmode=129,dir=1,};
	data[303]={action="Wipf",x=433,y=31,clrmod=0xff404040,scale=119,blitmode=129,r=19,};
	data[304]={action="Wipf",x=171,y=393,scale=107,r=-127,};
	data[305]={action="Wipf",x=18,y=114,clrmod=0xff404040,scale=29,blitmode=129,};
	data[306]={action="Wipf",x=816,y=68,clrmod=0x80808080,scale=36,};
	data[307]={action="Wipf",x=105,y=389,clrmod=0x80808080,scale=99,r=-177,dir=1,};
	data[308]={action="Wipf",x=461,y=125,clrmod=0xff404040,scale=52,blitmode=129,dir=1,};
	data[309]={action="Wipf",x=670,y=677,clrmod=0xff404040,scale=74,blitmode=129,dir=1,};
	data[310]={action="Wipf",x=682,y=632,clrmod=0xff404040,scale=55,blitmode=129,};
	data[311]={action="Wipf",x=888,y=659,clrmod=0xff404040,blitmode=129,};
	data[312]={action="Wipf",x=316,y=147,clrmod=0xff404040,blitmode=129,r=-52,};
	data[313]={action="Wipf",x=355,y=443,clrmod=0xff404040,scale=40,blitmode=129,dir=1,};
	data[314]={action="Wipf",x=663,y=164,clrmod=0xff404040,blitmode=129,dir=1,};
	data[315]={action="Wipf",x=614,y=203,scale=50,plane=50,};
	data[316]={action="Wipf",x=365,y=8,clrmod=0x40ffffff,scale=50,plane=50,r=-90,};
	data[317]={action="Wipf",x=158,y=141,clrmod=0x40ffffff,scale=50,plane=50,};
	data[318]={action="Wipf",x=967,y=137,clrmod=0x40ffffff,scale=50,plane=50,r=-90,};
	data[319]={action="Wipf",x=382,y=425,clrmod=0x40ffffff,scale=50,plane=50,r=90,};
	data[320]={action="Wipf",x=162,y=517,clrmod=0x40ffffff,scale=50,plane=50,r=-90,};
	data[321]={action="Wipf",x=861,y=98,clrmod=0x40ffffff,scale=50,plane=50,};
	data[322]={action="Wipf",x=303,y=331,clrmod=0x40ffffff,plane=50,};
	data[323]={action="Wipf",x=637,y=498,clrmod=0x40ffffff,scale=50,plane=50,r=90,};
	data[324]={action="Wipf",x=864,y=219,clrmod=0x40ffffff,scale=50,plane=50,r=-90,};
	data[325]={action="Wipf",x=200,y=499,clrmod=0x40ffffff,scale=50,plane=50,r=90,};
	data[326]={action="Wipf",x=514,y=450,clrmod=0x40ffffff,plane=50,};
	data[327]={action="Wipf",x=657,y=538,clrmod=0x40ffffff,plane=50,};
	data[328]={action="Wipf",x=415,y=168,clrmod=0x40ffffff,plane=50,r=180,};
	data[329]={action="Wipf",x=368,y=367,clrmod=0x40ffffff,scale=50,plane=50,r=180,};
	data[330]={action="Wipf",x=658,y=192,plane=50,r=-45,};
	data[331]={action="Wipf",x=915,y=522,clrmod=0x808080ff,scale=111,plane=-50,dir=1,};
	data[332]={action="Wipf",x=606,y=228,clrmod=0x808080ff,scale=117,plane=-50,r=-106,dir=1,};
	data[333]={action="Wipf",x=1195,y=5,clrmod=0x808080ff,scale=41,plane=-50,r=-36,};
	data[334]={action="Wipf",x=634,y=241,clrmod=0x808080ff,scale=75,plane=-50,r=-169,dir=1,};
	data[335]={action="Wipf",x=1104,y=224,clrmod=0x808080ff,scale=77,plane=-50,};
	data[336]={action="Wipf",x=793,y=83,clrmod=0x808080ff,scale=75,plane=-50,r=-15,};
	data[337]={action="Wipf",x=560,y=111,clrmod=0x808080ff,scale=74,plane=-50,r=84,dir=1,};
	data[338]={action="Wipf",x=397,y=11,clrmod=0x808080ff,scale=82,plane=-50,dir=1,};
	data[339]={action="Wipf",x=146,y=153,clrmod=0x808080ff,scale=38,plane=-50,r=-94,};
	data[340]={action="Wipf",x=197,y=157,clrmod=0x808080ff,scale=115,plane=-50,};
	data[341]={action="Wipf",x=785,y=503,clrmod=0x808080ff,scale=80,plane=-50,};
	data[342]={action="Wipf",x=702,y=508,clrmod=0x808080ff,scale=94,plane=-50,dir=1,};
	data[343]={action="Wipf",x=1201,y=513,clrmod=0x808080ff,scale=87,plane=-50,};
	data[344]={action="Wipf",x=481,y=66,clrmod=0x808080ff,scale=34,plane=-50,};
	data[345]={action="Wipf",x=66,y=238,clrmod=0x808080ff,scale=44,plane=-50,dir=1,};
	data[346]={action="Wipf",x=288,y=198,clrmod=0x808080ff,scale=104,plane=-50,r=-130,dir=1,};
	data[347]={action="Wipf",x=135,y=249,plane=-50,r=-90,};
	data[348]={action="Wipf",x=828,y=174,plane=-50,r=-90,dir=1,};
	data[349]={action="Wipf",x=655,y=469,plane=-50,r=90,dir=1,};
	data[350]={action="Wipf",x=334,y=199,scale=50,plane=-50,r=180,};
	data[351]={action="Wipf",x=1036,y=510,scale=50,plane=-50,};
	data[352]={action="Wipf",x=556,y=140,scale=50,plane=-50,r=90,};
	data[353]={action="Wipf",x=775,y=185,scale=50,plane=-50,};
	data[354]={action="Wipf",x=452,y=100,scale=50,plane=-50,};
	data[355]={action="Wipf",x=262,y=187,scale=50,plane=-50,r=180,};
	data[356]={action="Wipf",x=962,y=511,scale=50,plane=-50,};
	data[357]={action="Wipf",x=971,y=156,scale=50,plane=-50,};
	data[358]={action="Wipf",x=445,y=171,scale=50,plane=-50,r=180,};
	data[359]={action="Wipf",x=742,y=246,scale=50,plane=-50,r=180,};
	data[360]={action="Wipf",x=543,y=168,clrmod=0xff808080,scale=50,plane=-50,r=180,};
	Quests = data;
	return true;
}
