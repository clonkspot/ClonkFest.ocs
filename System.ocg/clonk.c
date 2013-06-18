#appendto Clonk
//PacMan Boundaries!
func Initialize()
{
	if(FindObject(Find_ID(Tools)))
		AddEffect("PacManBounds", this, 50, 1, this);
}

func FxPacManBoundsTimer()
{
	if(GetX() == LandscapeWidth()-4)
	SetPosition(5, GetY());
	
	if(GetX() == 4)
	SetPosition(LandscapeWidth()-5, GetY());
}

func Death()
{
	inherited(...);
	var ghost = CreateObject(Clonk, 0, 0, GetOwner());
	SetProperty("isGhost", 1, ghost);
	ghost.ContactIncinerate = 0;
	ghost -> AddEffect("Heal", ghost, 20, 1, ghost);
	ghost -> SetOwner(GetOwner());
	ghost -> MakeCrewMember(GetOwner());
	ghost -> SetCursor(GetOwner(), ghost);
	ghost -> SetPosition(LandscapeWidth()/2, LandscapeHeight()/2);
	ghost -> SetClrModulation(RGBa(128, 128, 128, 100));
}

func HasProperty(string what) {return this[what];}

func FxHealTimer()
{
	DoEnergy(100);
}