/* Functionality to disable Clonk control */

#appendto Clonk

func ObjectControl()
{
	if (g_controls_disabled) return true;
	return _inherited(...);
}
