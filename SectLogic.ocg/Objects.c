/* Automatically created objects file */

func InitializeObjects()
{
	var WoodenBridge001 = CreateObjectAbove(WoodenBridge, 170, 166);
	WoodenBridge001.Plane = -20;
	var WoodenBridge002 = CreateObject(WoodenBridge, 268, 160);
	WoodenBridge002.Plane = -20;
	var WoodenBridge003 = CreateObject(WoodenBridge, 66, 160);
	WoodenBridge003.Plane = -20;
	var WoodenBridge004 = CreateObjectAbove(WoodenBridge, 170, 180);
	WoodenBridge004.Plane = -20;
	var WoodenBridge005 = CreateObject(WoodenBridge, 268, 174);
	WoodenBridge005.Plane = -20;
	var WoodenBridge006 = CreateObject(WoodenBridge, 66, 174);
	WoodenBridge006.Plane = -20;
	CreateObjectAbove(Chest, 131, 151);
	CreateObjectAbove(Chest, 236, 152);
	CreateObjectAbove(Chest, 205, 152);
	CreateObjectAbove(Chest, 304, 151);
	CreateObjectAbove(Chest, 36, 151);
	CreateObjectAbove(Chest, 97, 151);

	var Clonk001 = CreateObjectAbove(Clonk, 152, 153);
	Clonk001->Unstick(7);
	Clonk001->SetDir(DIR_Left);
	var Clonk002 = CreateObjectAbove(Clonk, 176, 153);
	Clonk002->SetDir(DIR_Right);
	Clonk002->Unstick(7);
	var Clonk003 = CreateObjectAbove(Clonk, 257, 153);
	Clonk003->Unstick(7);
	Clonk003->SetDir(DIR_Left);
	var Clonk004 = CreateObjectAbove(Clonk, 284, 153);
	Clonk004->SetDir(DIR_Right);
	Clonk004->Unstick(7);
	var Clonk005 = CreateObjectAbove(Clonk, 55, 153);
	Clonk005->Unstick(7);
	Clonk005->SetDir(DIR_Left);
	var Clonk006 = CreateObjectAbove(Clonk, 79, 153);
	Clonk006->SetDir(DIR_Right);
	Clonk006->Unstick(7);
	return true;
}
