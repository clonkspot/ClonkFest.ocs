#appendto Arrow

public func SetStackCount(int amount)
{
	count = MaxStackCount();
	UpdateStackDisplay();
}

public func Hit()
{
	if(GetEffect("HitCheck",this))
		RemoveObject();
}

public func HitObject(object obj)
{
	if(obj->GetOCF() & OCF_CrewMember) return;
	inherited(obj,...);
	RemoveObject();
}

func UpdatePicture()
{
	SetGraphics("1");
}

local ContactIncinerate = 0;