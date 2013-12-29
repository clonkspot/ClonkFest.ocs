/* Load scenario section: Keeps game object and some needed, internal objects. Kills the rest. */

static g_loading_section;

global func LoadScenarioSectionClonkFest(string section, object game)
{
	// Store objects that need to survive section change
	// Goal is game object. HUD recreates itself. Not much to be done so far...
	g_loading_section = true;
	var obj, stored_objs = [];
	if (game) ClonkFestStoreSectObj(stored_objs, game);
	ClonkFestStoreSectObj(stored_objs, Goal_ClonkFest);
	// Laod section
	LoadScenarioSection(section, 0 /*C4SECT_KeepEffects*/);
	// Restore saved objects
	for (obj in stored_objs) if (obj) obj->SetObjectStatus(1);
	g_loading_section = false;
	return true;
}

global func ClonkFestStoreSectObj(array stored_objs, obj)
{
	if (!obj) return 0;
	if (GetType(obj) == C4V_Def)
	{
		var n;
		for (var obj2 in FindObjects(Find_ID(obj)))
			if (ClonkFestStoreSectObj(stored_objs, obj2)) ++n;
		return n;
	}
	else
	{
		if (obj->GetObjectStatus() == 2) return 0;
		var cont = obj->Contained();
		if (cont) ClonkFestStoreSectObj(stored_objs, cont);
		stored_objs[GetLength(stored_objs)] = obj;
		obj->SetObjectStatus(2);
		return 1;
	}
}