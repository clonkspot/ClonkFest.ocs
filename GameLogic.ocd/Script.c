/*-- 
	Party game: Logic
	Author: Sven2
	
	Solve the logic puzzle
--*/

#include GameBase

local Name = "$Name$";
local Description = "$Description$";

func GetGameAuthor() { return "Sven2"; }
func GetGameSection() { return "Logic"; }
func GetGameClonkMaxEnergy() { return 42; }
func GetGameStartPos(int player, int start_index, int max_index) { return {x=100+Random(120), y=224}; }
func GetGameClonkMaxContents() { return 1; }
func GetGameTimeLimit() { return 300; }

local correct_pos, correct_x, correct_index;
local hint_clonks, hint_containers, hint_items, hint_skins;
local answers;
local n_answers;
local hints, n_hints;

func InitGame(array players)
{
	// Black background
	SetSkyAdjust(0xff000000);
	// Bridges can be passed
	for (var bridge in FindObjects(Find_ID(WoodenBridge))) bridge->SetHalfVehicleSolidMask(true);
	// Find lorries and clonks to adjust
	var obj, arr, i;
	hint_clonks = FindObjects(Find_ID(Clonk), Find_Owner(NO_OWNER));
	hint_containers = FindObjects(Find_ID(Chest));
	n_answers = GetLength(hint_clonks);
	answers = CreateArray();
	for (i = 0; i < n_answers; ++i) answers[i] = i;
	for (arr in [hint_clonks, hint_containers])
	{
		for (obj in arr) obj.puzzle_x = obj->GetX();
		SortArrayByProperty(arr, "puzzle_x");
	}
	// Half of the containers should be lorries
	for (i in GetRandomAnswerSubset(n_answers/2))
	{
		var chest = hint_containers[i];
		hint_containers[i] = CreateObject(Lorry, chest->GetX(), chest->GetY());
		chest->RemoveObject();
	}
	// Skins for the clonks
	hint_skins = ShuffleArray([0, 1, 2, 3, "MaleBlackHair", "DarkSkinned"]);
	i = 0;
	for (obj in hint_clonks) obj->SetAlternativeSkin(hint_skins[i++]);
	// Distribute items
	hint_items = CreateArray(n_answers);
	correct_index = Random(n_answers);
	for (i = 0; i < n_answers; ++i) hint_items[i] = Translate(Format("Item%d", i));
	ShuffleArray(hint_items);
	for (i = 0; i < n_answers; ++i) hint_containers[i]->CreateContents([Rock, Treasure][i == correct_index]);
	// Treasure and container names (can't use get name because they should be lowercase in English)
	for (i = 0; i < n_answers; ++i) hint_containers[i] = ["$Lorry$", "$Chest$"][hint_containers[i]->GetID() == Chest];
	hint_items[correct_index] = "$Treasure$";
	// Build hint list
	hints = [];
	AddDecoyHint();
	i = 2; while (i--) AddMediumHint(correct_index);
	i = n_answers; while (i--) AddMediumHint(i);
	i = Random(n_answers);
	while (n_hints < 20)
	{
		if (i != correct_index) if (Random(3)) AddGoodHint(i); else AddMediumHint(i);
		i = (i + 1) % n_answers;
	}
	SortArrayByProperty(hints, "_");
	// Show hints in GUI
	OpenHintGUI();
	for (var hint in hints)
	{
		AddHint2GUI(hint.text);
	}
	// Clonk check timer
	correct_x = 24 + correct_index * 48;
	AddTimer(this.KillCheck, 5);
	// Collection check
	for (var player in players)
		if ((obj = GetCrew(player)))
			obj.Collection2 = this.Clonk_Collection2;
	// Player deactivation
	return inherited(players, ...);
}

private func AddMediumHint(i_item)
{
	var item = hint_items[i_item];
	var left_item, right_item;
	var skin = hint_skins[i_item];
	if (i_item) left_item = hint_items[Random(i_item)];
	if (i_item < n_answers-1) right_item = hint_items[n_answers-1-Random(n_answers-1-i_item)];
	// Has no beard
	if (!Random(8) && skin != "MaleBlackHair") return AddHint("$ClonkNoBeardHint$", item);
	// Item is near the border
	if (!Random(6)) return AddHint("$BorderHint$", item, ["", " $Not$"][(i_item > 0) && (i_item < n_answers-1)]);
	// Item is in the left/right half
	if (!Random(5)) return AddHint("$HalfHint$", item, ["$Left$", "$Right$"][i_item>=n_answers/2]);
	// Item is in a male/female clonk
	if (!Random(4)) return AddHint("$ClonkGenderHint$", item, ["$GenderMale$", "$GenderFemale$"][skin == 1 || skin == 3]);
	// Item is in a lorry/chest
	if (!Random(3)) return AddHint("$ContainerHint$", item, hint_containers[i_item]);
	// Item is between
	if (!Random(2) && left_item && right_item) return AddHint("$BetweenHint$", item, hint_items[i_item-1], hint_items[i_item+1]);
	// Item is right of
	if (left_item && (!Random(2) || !right_item)) return AddHint("$RightOfHint$", item, left_item);
	// Item is left of
	return AddHint("$LeftOfHint$", item, right_item);
}

private func AddGoodHint(i_item)
{
	var item = hint_items[i_item];
	// Item is in slot X
	if (!Random(6)) return AddHint("$SlotLeftHint$", item, Translate(Format("Index%d", i_item)));
	if (!Random(5)) return AddHint("$SlotRightHint$", item, Translate(Format("Index%d", n_answers-1-i_item)));
	// Has a beard
	if (Random(3) && hint_skins[i_item] == "MaleBlackHair") return AddHint("$ClonkBeardHint$", item);
	// One of two places
	if (!Random(3))
	{
		var other_place = Random(n_answers-1);
		if (other_place >= i_item) ++other_place;
		AddHint("$TwoSlotsLeftHint$", item, Translate(Format("Index%d", i_item)), Translate(Format("Index%d", other_place)));
	}
	// Container type from left/right
	if (!Random(2))
	{
		var i_cont_left = 0, i=0;
		for (var i=0; i<i_item; ++i) i_cont_left += (hint_containers[i] == hint_containers[i_item]);
		return AddHint("$SlotLeftContHint$", item, Translate(Format("Index%d", i_cont_left)), hint_containers[i_item]);
	}
	var i_cont_right = 0, i=0;
	for (var i=n_answers-1; i>i_item; --i) i_cont_right += (hint_containers[i] == hint_containers[i_item]);
	return AddHint("$SlotRightContHint$", item, Translate(Format("Index%d", i_cont_right)), hint_containers[i_item]);
}

private func AddDecoyHint()
{
	if (!Random(2)) return AddHint(Translate(Format("DecoyTreasure%d", Random(5))));
	var decoy_item = hint_items[Random(n_answers)];
	return AddHint(Translate(Format("Decoy%d", Random(5))), decoy_item);
}

private func AddHint(string, ...)
{
	// Add hint but avoid duplicates
	var hint_text = Format(string, ...);
	for (var hint in hints) if (hint.text == hint_text) return hint;
	return hints[n_hints++] = { text=hint_text, _=Random(16384) };
}

private func KillCheck()
{
	// Kill all clonks in the wrong section
	for (var clonk in FindObjects(Find_InRect(24, 128, 298, 40), Find_ID(Clonk), Find_OCF(OCF_Alive), Find_Not(Find_Owner(NO_OWNER)), Find_Not(Find_Func("IsGhost"))))
		if (!Inside(clonk->GetX(), correct_x, correct_x+40))
			clonk->Kill();
}

func Clonk_Collection2(object obj)
{
	if (obj->GetID() == Treasure && g_game) g_game->FinishGame();
	Call(Clonk.Collection2, obj, ...);
}

func OnGameFinished()
{
	// Winner: The one who has a treasure
	var winners = [], crew;
	for (var obj in FindObjects(Find_ID(Treasure)))
		if (crew = obj->Contained())
			if (crew->GetOwner() != NO_OWNER)
				winners[GetLength(winners)] = crew->GetOwner();
	if (!GetLength(winners)) return 1; // nobody found it
	SetGameWinners(winners, true);
	ScheduleCall(this, this.EndSequence, 25, 10, winners);	//Effects at winner Clonks
	return 125;
}

func EndSequence(winners)
{
	for (var plr in winners)
	{
		var crew = GetCrew(plr);
		if (crew)
		{
			crew->Sound("Objects::Balloon::Pop");
			crew->CreateParticle("MagicSpark", RandomX(-5,5),RandomX(-15,-10), PV_Random(-30,30), PV_Random(-30,30), PV_Random(10,50), Particles_Colored(Particles_Spark(),0xff8000,0xffff00), 15);
		}
	}
	return true;
}

// Get random n of n_answers
private func GetRandomAnswerSubset(int n)
{
	var all = answers[:], na = n_answers;
	var result = CreateArray(n);
	while (n--)
	{
		var i = Random(na);
		result[n] = all[i];
		all[i] = all[--na];
	}
	return result;
}


/* GUI */

local container, container_id; // container window containing menu entries and other stuff
local menu; // the actual menu (a MenuStyle_List)
local hint_item_idx;

private func OpenHintGUI()
{
	// Put all hints into a list menu
	menu = CreateObject(MenuStyle_List);
	menu->SetPermanent(true);
	menu->SetFitChildren();
	menu.Right = "100% - 1em";
	menu.Player = nil; // all players
	menu.BackgroundColor = 0x00000000;
	menu.Visibility = VIS_All;
	// overall container
	container =
	{
		Left = "100% - 20em",
		Top = "4em",
		Right = "100% - 2em",
		Bottom = "100% - 0.5em",
		Style = GUI_Multiple,
		Target = menu, // bind visibility to menu object
		ID = 0xffffee,
		BackgroundColor = 0x00000000,
		menu = menu
	};
	container_id = GuiOpen(container);
	hint_item_idx = 0;
	return true;
}

public func Destruction(...)
{
	if (container_id) GuiClose(container_id);
	if (menu) menu->RemoveObect();
	return _inherited(...);
}

private func AddHint2GUI(string hint, bool available, proplist entry)
{
	if (!menu) return false;
	var item_idx = hint_item_idx++;
	menu->AddItem(Icon_Lightbulb, hint, item_idx, this, this.ItemClicked, item_idx, nil, container_id, true);
	return true;
}

private func ItemClicked(...) {} // ignore click on hint
