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
	CastParticles("Spark",15,10,0,ReturnHeight()/2-1,15,30,RGB(255,255,150),RGB(255,255,200));
	Sound("Clang?");
}

func ReturnDamage()
{
	return(180);
}

func ReturnValue()
{
	return(50);
}