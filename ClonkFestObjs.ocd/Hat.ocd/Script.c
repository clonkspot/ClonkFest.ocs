/*--- Hat ---*/


public func Entrance(object container)
{
	if(container->GetID() == Clonk)
	{
		container->AttachMesh(Hat, "skeleton_head", "Bone");
	}
}

local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local Rebuy = true;
