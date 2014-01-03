/*-- 
	Moving Bricks 
	
	
--*/

local size; // Length of the brick.

protected func Initialize()
{
	SetAction("Float");
	return;
}


/*-- Destruction --*/

public func GetStrength() { return 180; }

protected func Damage()
{
	// Destroy if damage above strength.
	if (GetDamage() >= GetStrength())
	{
		var particle = Particles_Spark();
		particle.R = 0xff;
		particle.G = 0xff;
		particle.B = PV_Random(150,200);
		CreateParticle("Dust", PV_Random(-10,10),0, PV_Random(-3,3), PV_Random(-3,3), PV_Random(8,10), particle, 15);
		return RemoveObject();
	}
	// Change appearance.
	DoGraphics();
	return;
}

private func DoGraphics()
{
	// Change appearance according to damage and strength.
	if (GetDamage() >= 2*GetStrength() / 3)
		SetGraphics("Cracked2");
	else if (GetDamage() >= GetStrength() / 3)
		SetGraphics("Cracked1");
	else
		SetGraphics("");
	return;
}


local ActMap = {
	Float = {
		Prototype = Action,
		Name = "Float",
		Procedure = DFA_FLOAT,
		Length = 1,
		Delay = 1,
		X = 0,
		Y = 0,
		Wdt = 40,
		Hgt = 8,
		NextAction = "Float",
	},
};
local Name = "EarthBrick";
