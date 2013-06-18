/**
	The Glow
	Attaches to "to" (See public func Set()). This is handled via local ActMap.

*/


local Plane=1001;

local ActMap = {
	Attach = {
		Prototype = Action,
		Name = "Attach",
		Procedure = DFA_ATTACH,
		Length = 1,
		Delay = 0,
		FacetBase=1,
		NextAction = "Hold",
	}
};

func Initialize()
{
	SetObjectBlitMode(GFX_BLIT_Additive);
}

func AttachTargetLost()
{
	return RemoveObject();
}


public func Set(to)
{
	SetAction("Attach", to);
}

