/* Automatically created objects file */

func InitializeObjects()
{
	var Trunk0016 = CreateObjectAbove(Trunk, 38, 257);
	Trunk0016->SetR(22);
	Trunk0016.Plane = -1;
	Trunk0016->SetPosition(38, 234);
	var Trunk0015 = CreateObjectAbove(Trunk, 208, 258);
	Trunk0015->SetR(53);
	Trunk0015.Plane = -1;
	Trunk0015->SetPosition(208, 243);
	var Trunk0017 = CreateObjectAbove(Trunk, 296, 172);
	Trunk0017->SetR(-142);
	Trunk0017.Plane = -1;
	Trunk0017->SetPosition(296, 152);
	var Trunk0019 = CreateObjectAbove(Trunk, 9, 97);
	Trunk0019->SetR(21);
	Trunk0019.Plane = -1;
	Trunk0019->SetPosition(9, 74);

	CreateObjectAbove(Fern, 23, 265);
	var Fern0005 = CreateObjectAbove(Fern, 244, 264);
	Fern0005->SetR(-31);
	Fern0005->SetPosition(244, 261);

	var Branch0009 = CreateObjectAbove(Branch, 27, 206);
	Branch0009->SetR(1);
	Branch0009->SetPosition(27, 203);
	var Branch0010 = CreateObjectAbove(Branch, 155, 183);
	Branch0010->SetR(109);
	Branch0010->SetPosition(155, 183);
	var Branch0011 = CreateObjectAbove(Branch, 279, 263);
	Branch0011->SetR(15);
	Branch0011->SetPosition(279, 260);
	var Branch0012 = CreateObjectAbove(Branch, 96, 263);
	Branch0012->SetR(1);
	Branch0012->SetPosition(96, 260);
	var Branch0013 = CreateObjectAbove(Branch, 261, 111);
	Branch0013->SetR(152);
	Branch0013->SetPosition(261, 111);

	CreateObjectAbove(Fern, 89, 104);
	CreateObjectAbove(Fern, 169, 95);
	CreateObjectAbove(Fern, 257, 100);
	return true;
}
