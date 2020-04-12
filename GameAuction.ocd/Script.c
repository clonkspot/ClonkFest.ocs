/*-- 
	Party game: Auction
	Author: Luchs
	
	Bid for the best weapons and kill everyone else!
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Luchs"; }
func GetGameSection() { return "HotIce"; }
func GetGameClonkMaxEnergy() { return 50; }
func GetGameStartPos(int player, int start_index, int max_index) { return {x=LandscapeWidth()/2-100+Random(100), y=WheelY}; }
func GetGameClonkMaxContents() { return 5; }

func IsGameLastManStanding() { return true; }

/* configuration */
local Weapons;
local AuctionRounds = 2;
local MinItemCount = 4, MaxItemCount = 10;
local BiddingCountdown = 20;
local MaxFightingTime = 300;
local WheelX, WheelY = 75;

func Initialize()
{
	Weapons =  [Blunderbuss, Bow, Club, GrenadeLauncher, Helmet, IronBomb, Javelin, Shield, SmokeBomb, Sword, Firestone, Dynamite, DynamiteBox, Lantern, WindBag];
	return inherited(...);
}

func InitializeMap(proplist map)
{
	map->Resize(40, 30);
	return Game_HotIce->InitializeMap(map);
}

local round, item_count, state;

func InitGame(array players)
{
	WheelX = LandscapeWidth() / 2;
	inherited(players);

	GUI_Controller->ShowWealth();
	for (var clonk in FindObjects(Find_ID(Clonk)))
	{
		clonk->MakeInvincible();
		SetWealth(clonk->GetOwner(), 100);
	}

	// Create a bridge
	for (var i = 0; i < 5; i++)
		CreateObjectAbove(WoodenBridge, WheelX + ((i%2)*2-1) * (i+1)/2 * WoodenBridge->GetDefWidth(), WheelY + WoodenBridge->GetDefHeight())->MakeInvincible();

	round = 0;
	item_count = BoundBy(GetLength(players) + 1, MinItemCount, MaxItemCount);
	return inherited(players, ...);
}

func StartGame(array players)
{
	inherited(players);
	StartAuction();
	return inherited(players, ...);
}

func StartAuction()
{
	ShuffleArray(Weapons);
	for (var i = 0; i < item_count; i++)
	{
		var weapon = Weapons[i % GetLength(Weapons)];
		var wheel = CreateObjectAbove(AuctionWheel, WheelX + ((i%2)*2-1) * (i+1)/2 * 20, WheelY);
		wheel->SetItem(weapon);
	}
	GUI_Clock->CreateCountdown(BiddingCountdown, nil, this, true);
	state = "bidding";
}

func DoAuction(object wheel)
{
	var bids = wheel->GetBids();
	var winner_index = 0;
	// Tiebreak: wealth, number of points
	for (var i = 1; i < GetLength(bids) && bids[i].bid == bids[winner_index].bid; i++)
	{
		var plr_winner    = GetPlayerByIndex(bids[winner_index].player_index);
		var plr_i         = GetPlayerByIndex(bids[i].player_index);
		var wealth_winner = GetWealth(plr_winner);
		var wealth_i      = GetWealth(plr_i);
		var score_winner  = g_clonk_fest->GetPlayerScore(plr_winner);
		var score_i       = g_clonk_fest->GetPlayerScore(plr_i);
		if (
			// higher wealth?
			wealth_winner < wealth_i
			// or same wealth, but lower score?
			|| (wealth_winner == wealth_i && score_winner > score_i)
		)
			winner_index = i;
	}
	var second_index = 1;
	if (winner_index > 0) second_index = 1;
	var winner = GetPlayerByIndex(bids[winner_index].player_index);
	var winner_bid = bids[winner_index].bid;
	var second = GetPlayerByIndex(bids[second_index].player_index);
	var second_bid = bids[second_index].bid;
	wheel->ShowWinner(winner, second, winner_bid, second_bid);
	TransferWin(winner, second_bid, wheel->GetItem());
}

func FinishAuction()
{
	var delay = 1;
	for (var wheel in FindObjects(Find_ID(AuctionWheel)))
	{
		ScheduleCall(this, this.DoAuction, delay, 0, wheel);
		delay += 50;
	}
	ScheduleCall(this, this.NextRound, delay + 90, 0);
	state = "waitfornextround";
}

func TransferWin(int plr, int cost, id item_id)
{
	//Log("%s wins %s for %d {{Icon_Wealth}}", GetPlayerName(plr), item->GetName(), cost);
	var clonk = GetCursor(plr);
	clonk->Message("{{%i}} ({{Icon_Wealth}} %d)", item_id, cost);
	clonk->Sound("FestWin*");
	Sound("UI::Cash", true, nil, plr);
	DoWealth(plr, -cost);
	var item = clonk->CreateContents(item_id);
	if (item_id == Blunderbuss)
		item->CreateContents(LeadBullet);
	else if (item_id == Bow)
		item->CreateContents(Arrow);
	else if (item_id == GrenadeLauncher)
		item->CreateContents(IronBomb);
}

func OnCountdownFinished()
{
	// Apart from distinguishing between bidding and fighting states, this also
	// masks a bug where OnCountdownFinished is called twice for some reason.
	if (state == "bidding")
		FinishAuction();
	else if (state == "fighting")
		FinishGame();
}

func NextRound()
{
	RemoveAll(Find_ID(AuctionWheel));
	if (++round >= AuctionRounds)
	{
		for (var obj in FindObjects(Find_Or(Find_ID(Clonk), Find_ID(WoodenBridge))))
		{
			obj->ClearInvincible();
			if (obj->GetID() == WoodenBridge)
				obj->Incinerate();
		}
		GUI_Clock->CreateCountdown(MaxFightingTime, nil, this, false);
		state = "fighting";
	}
	else
	{
		StartAuction();
	}
}
