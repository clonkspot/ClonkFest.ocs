/**
	@author Dustin Ne� (dness.de)
*/

protected func Construction()
{
	SetProperty("MeshTransformation", Trans_Mul(Trans_Rotate(RandomX(-50,50),0,10), Trans_Scale(500)));
}