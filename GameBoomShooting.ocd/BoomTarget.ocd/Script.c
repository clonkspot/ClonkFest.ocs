local hit_cb;
local score = 0;

local remove = new Effect
{
	Timer = func()
	{
		Target->Fireworks();
		Target->RemoveObject();
	}
};

func Initialize()
{
	SetGraphics(nil, [Barrel, PowderKeg][Random(2)]);
	while (score == 0)
		score = Random(60) * 5 - 50;
	var clr;
	if (score >= 100) clr = 0xffff00;
	else if (score < 0) clr = 0xff3300;
	else clr = 0xffffff;
	CustomMessage(Format("@<c %x>%d</c>", clr, score), this, NO_OWNER, 0, 31+GetCon()/10);
	this->CreateEffect(remove, 1, 900);
}

func WeaponCanHit() { return 1; }
func IsProjectileTarget() { return 1; }
func OnProjectileHit(object target)
{
	//Log("Projectile Hit by %s, score %i", GetPlayerName(target->GetOwner()), score);
	if (hit_cb)
		hit_cb->OnTargetHit(score, target->GetOwner());
	RemoveObject();
}
