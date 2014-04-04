/* Automatically created objects file */

func InitializeObjects()
{
	CreateObject(Trunk, 77, 102);

	CreateObject(Tree_Coconut, 240, 108);

	var Chest0001 = CreateObject(Chest, 170, 438);
	Chest0001->SetClrModulation(0xffffff00);
	var Chest0002 = CreateObject(Chest, 62, 438);
	Chest0002->SetClrModulation(0xffff0000);
	var Chest0003 = CreateObject(Chest, 281, 439);
	Chest0003->SetClrModulation(0xffff8000);

	CreateObject(Foundry, 29, 309);

	var Butterfly0048 = CreateObject(Butterfly, 119, 33);
	Butterfly0048->SetComDir(COMD_DownLeft);
	Butterfly0048->SetXDir(-19);
	Butterfly0048->SetYDir(2);
	Butterfly0048->SetCommand("MoveTo", nil, 91, 35, nil, nil);
	Butterfly0048->SetAction("Flutter");
	Butterfly0048->SetPhase(9);

	Chest0001->CreateContents(Loam);
	Chest0001->CreateContents(Loam);
	Chest0001->CreateContents(Loam);
	Chest0002->CreateContents(Loam);
	Chest0003->CreateContents(Loam);
	var Loam0015 = CreateObject(Loam, 105, 247);
	Loam0015->SetR(93);
	Loam0015->SetPosition(105, 247);
	var Loam0016 = CreateObject(Loam, 98, 151);
	Loam0016->SetR(-52);
	Loam0016->SetPosition(98, 149);
	var Loam0017 = CreateObject(Loam, 242, 160);
	Loam0017->SetR(10);
	Loam0017->SetPosition(242, 157);
	var Loam0018 = CreateObject(Loam, 323, 229);
	Loam0018->SetR(-131);
	Loam0018->SetPosition(323, 227);
	var Loam0019 = CreateObject(Loam, 287, 149);
	Loam0019->SetR(-67);
	Loam0019->SetPosition(287, 148);
	var Loam0020 = CreateObject(Loam, 34, 341);
	Loam0020->SetR(-140);
	Loam0020->SetPosition(34, 339);
	var Loam0021 = CreateObject(Loam, 180, 124);
	Loam0021->SetR(-77);
	Loam0021->SetPosition(180, 123);
	var Loam0022 = CreateObject(Loam, 82, 232);
	Loam0022->SetR(78);
	Loam0022->SetPosition(82, 231);

	var WindBag0009 = Chest0001->CreateContents(WindBag);
	WindBag0009->SetR(-45);

	Chest0002->CreateContents(Bow);
	Chest0003->CreateContents(Bow);

	var Arrow0012 = Chest0002->CreateContents(Arrow);
	Arrow0012->SetR(90);
	var Arrow0013 = Chest0003->CreateContents(Arrow);
	Arrow0013->SetR(90);

	var Dynamite0029 = CreateObject(Dynamite, 205, 294);
	Dynamite0029->SetR(-84);
	Dynamite0029->SetPosition(205, 291);
	var Dynamite0030 = CreateObject(Dynamite, 99, 278);
	Dynamite0030->SetR(-125);
	Dynamite0030->SetPosition(99, 275);
	var Dynamite0031 = CreateObject(Dynamite, 258, 224);
	Dynamite0031->SetR(-4);
	Dynamite0031->SetPosition(258, 219);

	CreateObject(Firestone, 43, 199);
	CreateObject(Firestone, 264, 131);
	CreateObject(Firestone, 295, 234);
	CreateObject(Firestone, 225, 336);
	CreateObject(Firestone, 126, 346);
	CreateObject(Firestone, 131, 135);
	return true;
}
