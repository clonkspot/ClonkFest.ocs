/* Automatically created objects file */

static g_Goal_Flag;

func InitializeObjects()
{
	CreateObject(Goal_FlagBase, 582, 136);

	var MovingBrick0002 = CreateObject(MovingBrick, 421, 246);
	MovingBrick0002->SetComDir(COMD_Left);
	MovingBrick0002->SetXDir(-10);
	MovingBrick0002->SetClrModulation(0xff80ff80);
	MovingBrick0002->MoveHorizontal(391, 466);
	MovingBrick0002->SetSize(3);
	var MovingBrick0004 = CreateObject(MovingBrick, 98, 161);
	MovingBrick0004->SetComDir(COMD_Up);
	MovingBrick0004->SetYDir(-10);
	MovingBrick0004->SetClrModulation(0xffff8080);
	MovingBrick0004->MoveVertical(67, 267);
	MovingBrick0004->SetSize(2);
	var MovingBrick0006 = CreateObject(MovingBrick, 361, 67);
	MovingBrick0006->SetComDir(COMD_Right);
	MovingBrick0006->SetXDir(10);
	MovingBrick0006->SetClrModulation(0xff404040);
	MovingBrick0006->MoveHorizontal(331, 381);
	MovingBrick0006->SetSize(2);
	var MovingBrick0008 = CreateObject(MovingBrick, 436, 69);
	MovingBrick0008->SetComDir(COMD_Left);
	MovingBrick0008->SetXDir(-10);
	MovingBrick0008->SetClrModulation(0xffff8080);
	MovingBrick0008->MoveHorizontal(413, 463);
	MovingBrick0008->SetSize(2);
	var MovingBrick0010 = CreateObject(MovingBrick, 405, 354);
	MovingBrick0010->SetComDir(COMD_Right);
	MovingBrick0010->SetXDir(10);
	MovingBrick0010->SetClrModulation(0xff80ff80);
	MovingBrick0010->MoveHorizontal(245, 445);
	var MovingBrick0012 = CreateObject(MovingBrick, 144, 353);
	MovingBrick0012->SetComDir(COMD_Right);
	MovingBrick0012->SetXDir(10);
	MovingBrick0012->SetClrModulation(0xff8080ff);
	MovingBrick0012->MoveHorizontal(96, 196);
	var MovingBrick0014 = CreateObject(MovingBrick, 539, 395);
	MovingBrick0014->SetComDir(COMD_Down);
	MovingBrick0014->SetYDir(10);
	MovingBrick0014->SetClrModulation(0xffffff80);
	MovingBrick0014->MoveVertical(250, 400);
	var MovingBrick0016 = CreateObject(MovingBrick, 446, 378);
	MovingBrick0016->SetComDir(COMD_Right);
	MovingBrick0016->SetXDir(6);
	MovingBrick0016->SetClrModulation(0xff8080ff);
	MovingBrick0016->MoveHorizontal(425, 475);
	MovingBrick0016->SetSize(3);
	var MovingBrick0018 = CreateObject(MovingBrick, 80, 39);
	MovingBrick0018->SetComDir(COMD_Left);
	MovingBrick0018->SetXDir(2);
	MovingBrick0018->SetClrModulation(0xff80ff80);
	MovingBrick0018->MoveHorizontal(55, 80);
	MovingBrick0018->SetSize(2);
	var MovingBrick0020 = CreateObject(MovingBrick, 98, 213);
	MovingBrick0020->SetComDir(COMD_Down);
	MovingBrick0020->SetYDir(10);
	MovingBrick0020->SetClrModulation(0xffff80ff);
	MovingBrick0020->MoveVertical(74, 274);
	MovingBrick0020->SetSize(2);
	var MovingBrick0022 = CreateObject(MovingBrick, 543, 107);
	MovingBrick0022->SetComDir(COMD_Left);
	MovingBrick0022->SetXDir(-10);
	MovingBrick0022->SetClrModulation(0xff80ffff);
	MovingBrick0022->MoveHorizontal(509, 559);
	MovingBrick0022->SetSize(2);
	var MovingBrick0024 = CreateObject(MovingBrick, 495, 421);
	MovingBrick0024->SetComDir(COMD_Right);
	MovingBrick0024->SetXDir(10);
	MovingBrick0024->SetClrModulation(0xffffff80);
	MovingBrick0024->MoveHorizontal(91, 591);
	MovingBrick0024->SetSize(2);
	var MovingBrick0026 = CreateObject(MovingBrick, 524, 445);
	MovingBrick0026->SetComDir(COMD_Right);
	MovingBrick0026->SetXDir(10);
	MovingBrick0026->SetClrModulation(0xffff8080);
	MovingBrick0026->MoveHorizontal(86, 586);
	MovingBrick0026->SetSize(1);
	var MovingBrick0028 = CreateObject(MovingBrick, 495, 262);
	MovingBrick0028->SetComDir(COMD_Left);
	MovingBrick0028->SetXDir(-10);
	MovingBrick0028->SetClrModulation(0xff8080ff);
	MovingBrick0028->MoveHorizontal(468, 518);
	MovingBrick0028->SetSize(1);
	var MovingBrick0030 = CreateObject(MovingBrick, 277, 85);
	MovingBrick0030->SetComDir(COMD_Left);
	MovingBrick0030->SetXDir(-10);
	MovingBrick0030->SetClrModulation(0xffff8080);
	MovingBrick0030->MoveHorizontal(130, 270);
	MovingBrick0030->SetSize(1);
	var MovingBrick0032 = CreateObject(MovingBrick, 249, 377);
	MovingBrick0032->SetComDir(COMD_Right);
	MovingBrick0032->SetXDir(10);
	MovingBrick0032->SetClrModulation(0xffff8080);
	MovingBrick0032->MoveHorizontal(226, 276);
	MovingBrick0032->SetSize(1);
	var MovingBrick0034 = CreateObject(MovingBrick, 333, 461);
	MovingBrick0034->SetComDir(COMD_Left);
	MovingBrick0034->SetXDir(-10);
	MovingBrick0034->SetClrModulation(0xff80ff80);
	MovingBrick0034->MoveHorizontal(84, 584);
	MovingBrick0034->SetSize(1);
	var MovingBrick0036 = CreateObject(MovingBrick, 293, 204);
	MovingBrick0036->SetComDir(COMD_Up);
	MovingBrick0036->SetYDir(-10);
	MovingBrick0036->SetClrModulation(0xff80ff80);
	MovingBrick0036->MoveVertical(47, 247);
	MovingBrick0036->SetSize(3);
	var MovingBrick0038 = CreateObject(MovingBrick, 358, 257);
	MovingBrick0038->SetComDir(COMD_Right);
	MovingBrick0038->SetXDir(10);
	MovingBrick0038->SetClrModulation(0xff80ffff);
	MovingBrick0038->MoveHorizontal(329, 404);
	MovingBrick0038->SetSize(3);
	var MovingBrick0040 = CreateObject(MovingBrick, 293, 78);
	MovingBrick0040->SetComDir(COMD_Down);
	MovingBrick0040->SetYDir(10);
	MovingBrick0040->SetClrModulation(0xff8080ff);
	MovingBrick0040->MoveVertical(47, 247);
	MovingBrick0040->SetSize(3);
	var MovingBrick0042 = CreateObject(MovingBrick, 600, 414);
	MovingBrick0042->SetComDir(COMD_Down);
	MovingBrick0042->SetYDir(10);
	MovingBrick0042->SetClrModulation(0xffff80ff);
	MovingBrick0042->MoveVertical(350, 450);
	MovingBrick0042->SetSize(3);
	var MovingBrick0044 = CreateObject(MovingBrick, 86, 383);
	MovingBrick0044->SetComDir(COMD_Up);
	MovingBrick0044->SetYDir(-10);
	MovingBrick0044->SetClrModulation(0xff8080ff);
	MovingBrick0044->MoveVertical(323, 423);
	MovingBrick0044->SetSize(2);
	var MovingBrick0048 = CreateObject(MovingBrick, 329, 257);
	MovingBrick0048->SetSize(2);

	var Chest0049 = CreateObject(Chest, 319, 248);

	g_Goal_Flag = CreateObject(Goal_Flag, 586, 134);
	g_Goal_Flag.StaticSaveVar = "g_Goal_Flag";

	var WindBag0063 = Chest0049->CreateContents(WindBag);
	WindBag0063->AddRestoreMode(Chest0049, 319, 237);
	WindBag0063->SetR(-45);
	var WindBag0066 = Chest0049->CreateContents(WindBag);
	WindBag0066->AddRestoreMode(Chest0049, 319, 237);
	WindBag0066->SetR(-45);

	var Firestone0069 = Chest0049->CreateContents(Firestone);
	Firestone0069->AddRestoreMode(Chest0049, 319, 237);
	var Firestone0071 = Chest0049->CreateContents(Firestone);
	Firestone0071->AddRestoreMode(Chest0049, 319, 237);
	var Firestone0073 = Chest0049->CreateContents(Firestone);
	Firestone0073->AddRestoreMode(Chest0049, 319, 237);
	var Firestone0075 = Chest0049->CreateContents(Firestone);
	Firestone0075->AddRestoreMode(Chest0049, 319, 237);
	var Firestone0077 = Chest0049->CreateContents(Firestone);
	Firestone0077->AddRestoreMode(Chest0049, 319, 237);
	return true;
}