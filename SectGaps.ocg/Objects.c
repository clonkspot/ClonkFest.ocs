/* Automatically created objects file */

static g_Goal_Flag;

func InitializeObjects()
{
	CreateObjectAbove(EnvPack_Candle, 43, 84);
	CreateObjectAbove(EnvPack_Candle, 228, 162);
	CreateObjectAbove(EnvPack_Candle, 86, 282);
	CreateObjectAbove(EnvPack_Candle, 165, 322);
	CreateObjectAbove(EnvPack_Lantern, 209, 50);
	CreateObjectAbove(EnvPack_Lantern, 49, 51);

	CreateObjectAbove(EnvPack_FenceRustic, 241, 371);
	CreateObjectAbove(EnvPack_FenceRustic, 225, 371);
	CreateObjectAbove(EnvPack_FenceRustic, 210, 370);
	CreateObjectAbove(EnvPack_FenceRustic, 162, 370);
	CreateObjectAbove(EnvPack_FenceRustic, 177, 371);
	CreateObjectAbove(EnvPack_FenceRustic, 193, 371);

	CreateObjectAbove(EnvPack_TreeTrunks, 182, 330);

	CreateObjectAbove(EnvPack_WineBarrel, 139, 370);

	CreateObjectAbove(EnvPack_Scarecrow, 120, 410);

	CreateObjectAbove(EnvPack_Bag, 234, 130);
	CreateObjectAbove(EnvPack_Bag, 242, 130);
	CreateObjectAbove(EnvPack_Bag, 238, 130);

	CreateObjectAbove(EnvPack_Crate, 84, 211);

	g_Goal_Flag = CreateObjectAbove(Goal_Flag, 131, 409);
	g_Goal_Flag->SetClrModulation(0xffffff00);
	g_Goal_Flag.StaticSaveVar = "g_Goal_Flag";
	return true;
}
