#appendto Bow

public func ControlUseHolding(object clonk, int x, int y)
{
	// Save new angle
	var angle = Angle(0,0,x,y);
	angle = Normalize(angle,-180);

	if(angle >  160) angle =  160;
	if(angle < -160) angle = -160;
	if(angle <  35 && angle >  -36)
	{
		if(angle<0)
		angle = -35;
		else
		angle = 35;
	}

	clonk->SetAimPosition(angle);
	
	return true;
}

local ContactIncinerate = 0;