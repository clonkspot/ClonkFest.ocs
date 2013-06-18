/*-- Torch (Uses the club model :/)

This is a torch that floats and glows as if it got put onto a wall.
All darkness stuff is handled in Darkness.ocd/script.c

 --*/

local glow1 = 0;  //The glow effect object 1.
local glow2 = 0;  // Glow object 2.

local ActMap = {  		//This makes the whole thing float.
				Burning ={
						Prototype = Action,
						Name="Burning",
						Length = 1,
						Delay = 0,
						FacetBase=1,
						Procedure=DFA_FLOAT,
						NextAction="Hold",
						}
				};
				
public func IsInteractable(object clonk)	//We have a spacebar menue if we stand in front of it.
{
	return(true);
}

public func Interact(object clonk)			//This gets called when we hit space!
{
	if(clonk->ContentsCount() < 7) {clonk -> CreateContents(Torch);Sound("SoftTouch2", false, 100,-1);}	//If the clonk has a free slot, we put the carryable torch dirctly into him
	else{CreateObject(Torch); Sound("Sizzle");}		//If the clonk is full, the carryable torch just falls onto the floor
	RemoveObject();		//We remove the floating torch
}


func Initialize()	//At creation
{
	SetProperty("MeshTransformation", Trans_Rotate(RandomX(-15,15),1,1,1));	//The floating torch is rotated randomly to create diversety
	SetAction("Burning");	//Makes it float (See local ActMap)
	MakeGlow();		//Adds the glow
	SetMeshMaterial("Torch");	//Since this is only the club model we give it a new texture to make it look more like a torch
	AddTimer("Burn", 4);	//Burn() is called every 4 frames and will makes flames
}

func Burn()
{
	CreateParticleAtBone("DuroFire","main",[8,0,0], [0,0,0], RandomX(25,35)); //Creates flames and puts them in front of the darkness
	if(!Random(1000))Sound("Fire", false, 7, nil, +1);	//Every now and then it plays a fire sound for athmosphere
}


private func MakeGlow() //This gets called, if we want to add a glow. 2 Objects for a "flickering" effect.
{
	glow1 = CreateObject(Glow1, 1, 1, NO_OWNER);  //Creates the glow
	glow1->Exit();  //Moves it outside of the carrier, because it got created inside the clonk
	glow1->Set(this);  //Attaches it to the container (clonk)
	glow1 -> SetRDir(1);  //Makes it rotate, for flickering. (Wich doesn't look as epic as I hoped :()
	
	glow2 = CreateObject(Glow2, 1, 1, NO_OWNER);
	glow2->Exit();
	glow2->Set(this);
	glow2 -> SetRDir(-1);
	
}

private func Destruction()  //We remove the 2 glows
{
    if (glow1 != nil)  //Make sure the engine knows what to remove. A pointer at "nil" is a no-no.
    {
		glow1->RemoveObject();
	}
	
	if (glow2 != nil)
    {
		glow2->RemoveObject();
	}
}


local Name = "$Name$";
local Description = "$Description$";
local Collectibe = 0;
