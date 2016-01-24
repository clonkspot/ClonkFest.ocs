/*--    DeadlyTool    --*/


#include AngryTool

func Initialize()
{
	inherited(...);
	SetGraphics(nil, Pickaxe);
}

protected func ContactBottom()
{
	inherited(...);
	var particle = Particles_Spark();
	particle.R = 0xff;
	particle.G = 0xff;
	particle.B = PV_Random(150,200);
	CreateParticle("MagicSpark", 0,ReturnHeight()/2-1, PV_Random(-10,10), PV_Random(-10,10), PV_Random(10,50), particle, 15);
	Sound("Hits::Materials::Metal::LightMetalHit?");
}

func ReturnDamage()
{
	return(180);
}
