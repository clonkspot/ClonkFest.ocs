#appendto Tree_Coniferous

local ContactIncinerate = 0;

func Initialize()
{
	if(FindObject(Find_ID(Pickers)))
		Schedule(this, "AddTimer(\"MakeBerry\", 120)", Random(120), 0);
}

func MakeBerry()
{
	if(ObjectCount(Find_OCF(OCF_NotContained),Find_ID(Sproutberry))<=10*GetPlayerCount())
	{
		if(!Random(3))
		{
		if(!Random(2))
		CreateObject(Sproutberry, RandomX(-30, 30), RandomX(-30, 0));
		else
		CreateObject(Sproutberry, RandomX(-15, 15), RandomX(-55, -30));
		}
	}
}