#appendto Lorry

local cooldown = false;

func Initialize()
{
	UpdateCount();
}

func Collection()
{
	UpdateCount();
}

func UpdateCount()
{
		
		var rgba = SplitRGBaValue(GetPlayerColor(GetOwner()));
		GetCrew(GetOwner())->Message(Format("@<c %x><c %x>%d/20</c> {{Sproutberry}}", RGBa(255, 255, 255, 180), RGBa(rgba[0], rgba[1], rgba[2], 180), ContentsCount(Sproutberry)));
		if(ContentsCount(Sproutberry)>=20)
		{
			pickerswinner = GetOwner();
			PickersEnd();
		}
}

func _ControlUp()	//Use this if the bounce off sucks
{
	if(this.cooldown) return;
	SetYDir(-20);
	Sound("lift", false, 50);
	this.cooldown = true;
	Schedule(this, "this.cooldown = false", 20, 0);
}