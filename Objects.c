/* Automatically created objects file */

func InitializeObjects()
{
	var Environment_Celestial0001 = CreateObject(Environment_Celestial, 0, 0);

	var Environment_Time0002 = CreateObject(Environment_Time, 0, 0);
	Environment_Time0002->SetTime(1204);
	Environment_Time0002->SetCycleSpeed(20);

	CreateObject(EnvPack_BridgeRustic, 313, 338);

	CreateObject(EnvPack_Crate, 413, 336);

	CreateObject(EnvPack_Bag, 246, 336);

	CreateObject(EnvPack_Painting, 568, 273);

	CreateObject(EnvPack_Guidepost, 280, 337);

	var EnvPack_Rail0027 = CreateObject(EnvPack_Rail, 286, 338);
	EnvPack_Rail0027->SetR(2);
	EnvPack_Rail0027->SetPosition(286, 331);
	var EnvPack_Rail0028 = CreateObject(EnvPack_Rail, 268, 339);
	EnvPack_Rail0028->SetR(-3);
	EnvPack_Rail0028->SetPosition(268, 332);
	CreateObject(EnvPack_Rail, 251, 338);
	CreateObject(EnvPack_Rail, 337, 339);

	CreateObject(EnvPack_Candle, 579, 283);

	var EnvPack_Candle_Shine0032 = CreateObject(EnvPack_Candle_Shine, 579, 283);
	EnvPack_Candle_Shine0032->SetClrModulation(0xc7ffffff);
	EnvPack_Candle_Shine0032->SetObjectBlitMode(GFX_BLIT_Additive);
	var EnvPack_Candle_Shine0033 = CreateObject(EnvPack_Candle_Shine, 579, 283);
	EnvPack_Candle_Shine0033->SetClrModulation(0xe4ffffff);
	EnvPack_Candle_Shine0033->SetObjectBlitMode(GFX_BLIT_Additive);
	var EnvPack_Candle_Shine0034 = CreateObject(EnvPack_Candle_Shine, 578, 283);
	EnvPack_Candle_Shine0034->SetClrModulation(0xc5ffffff);
	EnvPack_Candle_Shine0034->SetObjectBlitMode(GFX_BLIT_Additive);

	CreateObject(EnvPack_Scarecrow, 608, 136);

	CreateObject(EnvPack_TreeTrunks, 531, 312);

	CreateObject(EnvPack_WineBarrel, 534, 361);
	CreateObject(EnvPack_WineBarrel, 556, 360);

	var Clonk0039 = CreateObject(Clonk, 564, 303);
	Clonk0039->SetCon(140);
	Clonk0039->SetColor(0xff0000);
	Clonk0039->SetObjectBlitMode(GFX_BLIT_Mod2);
	Clonk0039->SetDir(DIR_Left);

	Clonk0039->CreateContents(Sword);
	return true;
}
