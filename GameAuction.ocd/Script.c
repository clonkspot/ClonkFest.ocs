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
func GetGameStartPos(int player, int start_index, int max_index) { return {x=WheelX-100+Random(100), y=WheelY}; }
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
	item_count = BoundBy(GetLength(players), MinItemCount, MaxItemCount);
}

func StartGame(array players)
{
	inherited(players);
	StartAuction();
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

func FinishAuction()
{
	// Bids are by player index (not player number).
	var auctions = [];
	for (var wheel in FindObjects(Find_ID(AuctionWheel)))
	{
		var auction = { wheel = wheel, item = wheel.item, bids = wheel->GetBids() };
		PushBack(auctions, auction);
	}
	// Determine cost according to VCG auction.
	var winners = FindWinners(auctions).winners;
	for (var i = 0; i < GetLength(auctions); i++)
	{
		var auction = auctions[i], winner = winners[i];
		if (winner == nil) continue;
		var v1 = FindWinners(auctions, winner).value;
		var v2 = FindWinners(auctions, winner, i).value;
		var cost = v1 - v2;
		var plr = GetPlayerByIndex(winner);
		TransferWin(plr, cost, auction.item);
		auction.wheel->ShowWinner(plr, cost);
	}
	Sound("UI::Cash", true);
	ScheduleCall(this, this.NextRound, 90, 0);
	state = "waitfornextround";
}

// Find winner for each item, which is the player with the highest bid.
// Optionally skip a player and/or and auction.
func FindWinners(array auctions, int skip_player, int skip_auction)
{
	// Create sorted list of bids.
	var bids = [];
	for (var i = 0; i < GetLength(auctions); i++)
	{
		if (i == skip_auction) continue;
		var auction = auctions[i];
		for (var j = 0; j < GetLength(auction.bids); j++)
			if (j != skip_player)
				PushBack(bids, {
					bid = auction.bids[j],
					player = j,
					auction = i,
				});
	}
	SortArrayByProperty(bids, "bid", true);

	// The idea here is to maximize value. However, this is only a simple
	// greedy algorithm for now...
	var wealth = WealthArray();
	var winners = CreateArray(GetLength(auctions));
	var value = 0;
	for (var i = 0; i < GetLength(bids); i++)
	{
		var bid = bids[i];
		if (winners[bid.auction] != nil) continue; // *cough*
		if (wealth[bid.player] >= bid.bid)
		{
			winners[bid.auction] = bid.player;
			value += bid.bid;
			wealth[bid.player] -= bid.bid;
		}
		else
		{
			// Not enough money - reduce bid and re-sort.
			bid.bid = wealth[bid.player];
			SortArrayByProperty(bids, "bid", true);
			i -= 1;
		}
	}

	return { winners = winners, value = value };
}

func WealthArray()
{
	var wealth = CreateArray(GetPlayerCount());
	for (var i = 0; i < GetPlayerCount(); i++)
		wealth[i] = GetWealth(GetPlayerByIndex(i));
	return wealth;
}

func TransferWin(int plr, int cost, id item_id)
{
	//Log("%s wins %s for %d {{Icon_Wealth}}", GetPlayerName(plr), item->GetName(), cost);
	DoWealth(plr, -cost);
	var item = GetCursor(plr)->CreateContents(item_id);
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
