/*--    DeadlyTool    --*/


#include AngryTool

func Initialize()
{
	inherited(...);
	SetGraphics(nil, Shovel);
}

func ContactBottom()
{
	inherited(...);
	var particle = Particles_Spark();
	particle.R = 0xff;
	particle.G = 0xff;
	particle.B = PV_Random(150,200);
	CreateParticle("Dust", 0,10, PV_Random(-3,3), PV_Random(-3,3), PV_Random(5,8), particle, 15);
	
//	CreateParticle(,0, 10, RandomX(-3,3),RandomX(-3,3),RandomX(50,75),DoRGBaValue(-7183302,128,0));
    Sound("Dig?");
}