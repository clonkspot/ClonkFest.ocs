/* Automatically created objects file */

func InitializeObjects()
{
	CreateObject(MovingBrick, 157, 48);
	CreateObject(MovingBrick, 50, 48);
	CreateObject(MovingBrick, 254, 48);
	CreateObject(MovingBrick, 235, 94);
	CreateObject(MovingBrick, 162, 126);
	CreateObject(MovingBrick, 92, 97);

	CreateObject(Rock, 49, 39);
	CreateObject(Rock, 254, 39);

	var WindBag0011 = CreateObject(WindBag, 163, 118);
	WindBag0011->SetR(-32);
	WindBag0011->SetPosition(163, 115);

	CreateObject(Firestone, 235, 85);
	CreateObject(Firestone, 91, 89);
	return true;
}
