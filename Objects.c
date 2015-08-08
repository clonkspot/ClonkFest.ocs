/* Automatically created objects file */

func InitializeObjects()
{
	var Environment_Time0002 = CreateObjectAbove(Environment_Time, 0, 0);
	Environment_Time0002->SetTime(1204);
	Environment_Time0002->SetCycleSpeed(20);

	CreateObjectAbove(EnvPack_BridgeRustic, 313, 338);

	CreateObjectAbove(EnvPack_Crate, 413, 336);

	CreateObjectAbove(EnvPack_Bag, 246, 336);

	CreateObjectAbove(EnvPack_Painting, 568, 273);

	CreateObjectAbove(EnvPack_Guidepost, 280, 337);

	var EnvPack_Rail0027 = CreateObjectAbove(EnvPack_Rail, 286, 338);
	EnvPack_Rail0027->SetR(2);
	EnvPack_Rail0027->SetPosition(286, 331);
	var EnvPack_Rail0028 = CreateObjectAbove(EnvPack_Rail, 268, 339);
	EnvPack_Rail0028->SetR(-3);
	EnvPack_Rail0028->SetPosition(268, 332);
	CreateObjectAbove(EnvPack_Rail, 251, 338);
	CreateObjectAbove(EnvPack_Rail, 337, 339);

	CreateObjectAbove(EnvPack_Candle, 579, 283);

	var EnvPack_Candle_Shine0032 = CreateObjectAbove(EnvPack_Candle_Shine, 579, 283);
	EnvPack_Candle_Shine0032->SetClrModulation(0xc7ffffff);
	EnvPack_Candle_Shine0032->SetObjectBlitMode(GFX_BLIT_Additive);
	var EnvPack_Candle_Shine0033 = CreateObjectAbove(EnvPack_Candle_Shine, 579, 283);
	EnvPack_Candle_Shine0033->SetClrModulation(0xe4ffffff);
	EnvPack_Candle_Shine0033->SetObjectBlitMode(GFX_BLIT_Additive);
	var EnvPack_Candle_Shine0034 = CreateObjectAbove(EnvPack_Candle_Shine, 578, 283);
	EnvPack_Candle_Shine0034->SetClrModulation(0xc5ffffff);
	EnvPack_Candle_Shine0034->SetObjectBlitMode(GFX_BLIT_Additive);

	CreateObjectAbove(EnvPack_Scarecrow, 608, 136);

	CreateObjectAbove(EnvPack_TreeTrunks, 531, 312);

	CreateObjectAbove(EnvPack_WineBarrel, 534, 361);
	CreateObjectAbove(EnvPack_WineBarrel, 556, 360);

	var Clonk0039 = CreateObjectAbove(Clonk, 564, 303);
	Clonk0039->SetCon(140);
	Clonk0039->SetColor(0xff0000);
	Clonk0039->SetObjectBlitMode(GFX_BLIT_Mod2);
	Clonk0039->SetDir(DIR_Left);

	Clonk0039->CreateContents(Sword);
	return true;
}
