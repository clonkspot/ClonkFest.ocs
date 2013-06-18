//Fire first melts away your wealth, then hurts you.

global func FxFireTimer(object target, proplist effect, int time)
{
	inherited(...);
	
	if(target->GetID() == Clonk && GetPlrWealth(target->GetOwner())>0)
	{
		DoWealth(target->GetOwner(), -10);
		CustomMessage(Format("<c %x> %d </c> {{GUI_Wealth}}",GetPlayerColor(target->GetOwner()), GetWealth(target->GetOwner())),target, NO_OWNER, 0, 0, );
	}
	
	else if(target->GetAlive())
	{
		target->DoEnergy(-effect.strength*4, true, FX_Call_EngFire, effect.caused_by);
		Message(Format("<c ff0000>Energy: %d", target->GetEnergy()));
		target->Hurt();
	}
}
