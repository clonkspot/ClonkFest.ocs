/*-- Auction Spin Wheel --*/

local item, bids;

protected func Initialize()
{
	SetGraphics(nil, SpinWheel);
	bids = [];
	ShowBids();
}

public func SetItem(id item)
{
	this.item = item;
	SetGraphics(nil, item, 1, GFXOV_MODE_IngamePicture);
	SetObjDrawTransform(1000, 0, 0, 0, 1000, -30000, 1);
}

private func ShowBids()
{
	CustomMessage("", this);
	for (var i = 0; i < GetPlayerCount(); i++)
	{
		var plr = GetPlayerByIndex(i);
		CustomMessage(Format("@{{Icon_Wealth}} %d", bids[plr]), this, plr, 0, 0, nil, nil, nil, MSG_Multiple);
	}
}

public func ShowWinner(int plr, int cost)
{
	// TODO: Color does not seem to work
	CustomMessage(Format("@%s|{{Icon_Wealth}} %d", GetPlayerName(plr), cost), this, nil, 0, 0, GetPlayerColor(plr));
}

public func GetBids()
{
	var b = CreateArray(GetPlayerCount());
	for (var i = 0; i < GetPlayerCount(); i++)
	{
		b[i] = bids[GetPlayerByIndex(i)];
	}
	return b;
}

private func AdjustBid(int plr, int by)
{
	bids[plr] = BoundBy((bids[plr] ?? 0) + by, 0, GetWealth(plr));
	ShowBids();
}

public func ControlUp(object clonk)
{
	AdjustBid(clonk->GetOwner(), +1);
}

public func ControlDown(object clonk)
{
	AdjustBid(clonk->GetOwner(), -1);
}

public func ControlLeft(object clonk)
{
	AdjustBid(clonk->GetOwner(), -10);
}

public func ControlRight(object clonk)
{
	AdjustBid(clonk->GetOwner(), +10);
}

local ActMap = {
	Still = {
		Prototype = Action,
		Name = "Still",
		Procedure = DFA_NONE,
		Length = 1,
		Delay = 1,
		NextAction = "Still",
		Animation = "SpinLeft",
	},
	SpinLeft = {
		Prototype = Action,
		Name = "SpinLeft",
		Procedure = DFA_NONE,
		Length = 36,
		Delay = 1,
		NextAction = "Still",
		Animation = "SpinLeft",
	},
	SpinRight = {
		Prototype = Action,
		Name = "SpinRight",
		Procedure = DFA_NONE,
		Length = 36,
		Delay = 1,
		NextAction = "Still",
		Animation = "SpinRight",
	},
};
local Name = "$Name$";
local Touchable = 2;
local Plane = 200;
