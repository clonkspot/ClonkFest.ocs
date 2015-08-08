/* Automatically created objects file */

func InitializeObjects()
{
	CreateObjectAbove(MovingBrick, 157, 48);
	CreateObjectAbove(MovingBrick, 50, 48);
	CreateObjectAbove(MovingBrick, 254, 48);
	CreateObjectAbove(MovingBrick, 235, 94);
	CreateObjectAbove(MovingBrick, 162, 126);
	CreateObjectAbove(MovingBrick, 92, 97);

	CreateObjectAbove(Rock, 49, 39);
	CreateObjectAbove(Rock, 254, 39);

	var WindBag0011 = CreateObjectAbove(WindBag, 163, 118);
	WindBag0011->SetR(-32);
	WindBag0011->SetPosition(163, 115);

	CreateObjectAbove(Firestone, 235, 85);
	CreateObjectAbove(Firestone, 91, 89);
	return true;
}
