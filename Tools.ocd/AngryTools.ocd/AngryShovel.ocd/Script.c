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
	CreateParticle("Dust",0, 10, RandomX(-3,3),RandomX(-3,3),RandomX(50,75),DoRGBaValue(-7183302,128,0));
    Sound("Dig?");
}