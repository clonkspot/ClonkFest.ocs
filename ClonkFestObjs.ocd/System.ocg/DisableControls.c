/* Functionality to disable Clonk control */

static g_controls_disabled;

// Disables controls and stops all Clonks
global func DisableAllControls(bool disable_clonks)
{
	g_controls_disabled = true;
	if (disable_clonks) for (var obj in FindObjects(Find_ID(Clonk)))
	{
		obj->SetCategory(C4D_StaticBack);
	}
	return true;
}

global func EnableAllControls(bool enable_clonks)
{
	g_controls_disabled = false;
	if (enable_clonks) for (var obj in FindObjects(Find_ID(Clonk)))
	{
		obj->SetCategory(C4D_Living);
	}
	return true;
}

global func ObjectControl(...)
{
	if (g_controls_disabled)
	{
		//Log("control disabled.");
		return true;
	}
	return _inherited(...);
}
