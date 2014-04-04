/* Automatically created objects file */

static g_Goal_Flag;

func InitializeObjects()
{
	CreateObject(EnvPack_Candle, 43, 84);
	CreateObject(EnvPack_Candle, 228, 162);
	CreateObject(EnvPack_Candle, 86, 282);
	CreateObject(EnvPack_Candle, 165, 322);
	CreateObject(EnvPack_Lantern, 209, 50);
	CreateObject(EnvPack_Lantern, 49, 51);

	CreateObject(EnvPack_FenceRustic, 241, 371);
	CreateObject(EnvPack_FenceRustic, 225, 371);
	CreateObject(EnvPack_FenceRustic, 210, 370);
	CreateObject(EnvPack_FenceRustic, 162, 370);
	CreateObject(EnvPack_FenceRustic, 177, 371);
	CreateObject(EnvPack_FenceRustic, 193, 371);

	CreateObject(EnvPack_TreeTrunks, 182, 330);

	CreateObject(EnvPack_WineBarrel, 139, 370);

	CreateObject(EnvPack_Scarecrow, 120, 410);

	CreateObject(EnvPack_Bag, 234, 130);
	CreateObject(EnvPack_Bag, 242, 130);
	CreateObject(EnvPack_Bag, 238, 130);

	CreateObject(EnvPack_Crate, 84, 211);

	g_Goal_Flag = CreateObject(Goal_Flag, 131, 409);
	g_Goal_Flag->SetClrModulation(0xffffff00);
	g_Goal_Flag.StaticSaveVar = "g_Goal_Flag";
	return true;
}
