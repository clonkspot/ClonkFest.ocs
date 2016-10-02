/* Automatically created objects file */

static g_Goal_Flag;

func InitializeObjects()
{
	CreateObjectAbove(Goal_FlagBase, 582, 136);
	var Chest001 = CreateObjectAbove(Chest, 589, 420);

	g_Goal_Flag = CreateObjectAbove(Goal_Flag, 586, 134);
	g_Goal_Flag.StaticSaveVar = "g_Goal_Flag";

	return true;
}
