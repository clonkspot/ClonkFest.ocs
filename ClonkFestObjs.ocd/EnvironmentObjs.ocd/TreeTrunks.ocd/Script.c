/**
	@author Dustin Ne� (dness.de)
*/

protected func Construction()
{
	SetProperty("MeshTransformation", Trans_Mul(Trans_Rotate(RandomX(-40,40),0,20), Trans_Scale(550)));
}