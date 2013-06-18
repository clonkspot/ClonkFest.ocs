/*-- Torch (Uses the club model :/)

This code is just here to make a glow effect if the torch is held in a hand.
It also handles the what happens when it's clicked/activated.
All darkness stuff is handled in Darkness.ocd/script.c

 --*/

local glow1 = nil;  //The glow effect object 1.
local glow2 = nil;  // Glow object 2.
local torch2 = nil;

private func Hit()
{
	Sound("WoodHit?");
}

public func GetCarryMode() { return CARRY_HandBack; }

public func IsWorkshopProduct() { return true; }
public func IsTool() { return true; }
public func IsToolProduct() { return true; }

func ControlUse(object clonk)	//When we use (click with) the object
{
	if(GetMaterial()==Material("Tunnel"))	//If we stand in front of tunnel the carryable torch will be deleted and a floating one will be created instead
	{
	torch2 = 1;			//This is one because it shouldn't sizzle.
	clonk->DoKneel();	//The Clonk makes an animation
	RemoveGlow();
	RemoveTimer("ShouldGlow");
	CreateObject(Torch2, 0 , 5);
	Exit();
	RemoveObject();
	}
	else
	{
	Message("Torch can only be attached to a wall!");
	return(true);
	}
}

func Initialize()
{
	local glowing = false;  //At the start, the torch doesn't glow
	SetMeshMaterial("Torch");
}

func Entrance()
{
	if(Contained()->GetID()!=Clonk){Sound("Sizzle", false, 10); torch2=1;}  //If we put it into something that's not a clonk, it sizzles
	else torch2 = 0;		//If the thing enters a clonk, and leaves it later, it should sizle.
	AddTimer("ShouldGlow", 10);	//We will only run the timer, when the Torch is contained.
}

func Departure()  //When it's outside, there's no glowing and no timer.
{
	if(!torch2)	  //If it gets out of something it checks if it should sizzle
	Sound("Sizzle", false, 10); 
	RemoveGlow();
	RemoveTimer("ShouldGlow");	
}

func ShouldGlow()
{
	if (Contained()->GetID() == Clonk) //We will add a glow object only if we know, the torch is inside a clonk
	{
		if(Contained()->GetHandItem(0) == this || Contained()->GetHandItem(1) == this)  //and currently selected in a hand
		{
			if(glowing == false) MakeGlow();  //and there's currently no glow object present
		}
		else if(glowing == true)
			RemoveGlow();  //If the torch is not in a hand, we remove the glow again.
	}
}

private func MakeGlow() //This gets called, if we want to add a glow. 2 Objects for a "flickering" effect.
{
	glow1 = CreateObject(Glow1, 1, 1, NO_OWNER);  //Creates the glow
	glow1->Exit();  //Moves it outside of the carrier, because it got created inside the clonk
	glow1->Set(Contained());  //Attaches it to the container (clonk)
	glow1 -> SetRDir(1);  //Makes it rotate, for flickering. (Wich doesn't look as epic as I hoped :()
	
	glow2 = CreateObject(Glow2, 1, 1, NO_OWNER);
	glow2->Exit();
	glow2->Set(Contained());
	glow2 -> SetRDir(-1);
	
	glowing = true;  //Now we have a glow!
	AddTimer("Burning",3);
}

private func RemoveGlow()  //If we want to remove the 2 glows
{
    if (glow1 != nil)  //Make sure the engine knows what to remove. A pointer at "nil" is a no-no.
    {
		glow1->RemoveObject();
		glowing = false;
	}
	
	if (glow2 != nil)
    {
		glow2->RemoveObject();
		glowing = false;
	}
	RemoveTimer("Burning");
}

func Burning()
{
	if(Contained()->GetAction()=="Walk"||Contained()->GetAction()=="Jump"||Contained()->GetAction()=="WallJump"||Contained()->GetAction()=="Roll")
	CreateParticle("DuroFire",8*Contained()->GetCalcDir(),-3,RandomX(-1,1),RandomX(-1,1),RandomX(25,50),RGB(255,255,255));
	else
	CreateParticle("DuroFire",-3*Contained()->GetCalcDir(),-9,RandomX(-1,1),RandomX(-1,1),RandomX(25,50),RGB(255,255,255));
	
}

func Definition(def) {
	SetProperty("PictureTransformation",Trans_Rotate(-30,0,0,1),def);
}

local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local Rebuy = true;

