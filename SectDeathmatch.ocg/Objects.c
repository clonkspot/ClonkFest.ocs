/* Automatically created objects file */

func InitializeObjects()
{
	var Chest0001 = CreateObject(Chest, 49, 231);
	var Chest0002 = CreateObject(Chest, 225, 232);

	Chest0001->CreateContents(Bow);
	Chest0002->CreateContents(Bow);

	Chest0001->CreateContents(Arrow);
	Chest0001->CreateContents(Arrow);
	Chest0001->CreateContents(Arrow);
	Chest0001->CreateContents(Arrow);
	Chest0001->CreateContents(Arrow);
	Chest0002->CreateContents(Arrow);
	Chest0002->CreateContents(Arrow);
	Chest0002->CreateContents(Arrow);
	Chest0002->CreateContents(Arrow);
	Chest0002->CreateContents(Arrow);
	return true;
}
