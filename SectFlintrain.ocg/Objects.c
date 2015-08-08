/* Automatically created objects file */

func InitializeObjects()
{
	CreateObjectAbove(Trunk, 92, 117);
	CreateObjectAbove(Trunk, 275, 180);

	var Catapult0003 = CreateObjectAbove(Catapult, 60, 210);
	Catapult0003->SetCon(75);
	Catapult0003->SetRDir(7);
	Catapult0003->SetClrModulation(0xff808080);

	var Lorry0005 = CreateObjectAbove(Lorry, 332, 286);
	Lorry0005->SetR(-29);
	Lorry0005->SetPosition(332, 276);

	CreateObjectAbove(Pickaxe, 55, 289);

	var Boompack0008 = CreateObjectAbove(Boompack, 294, 108);
	Boompack0008->SetColor(0xff);

	CreateObjectAbove(Crate, 166, 324);
	CreateObjectAbove(Crate, 205, 324);
	CreateObjectAbove(Crate, 233, 325);
	return true;
}
