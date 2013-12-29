// Helper functions to make animals invincible

global func MakeInvincible()
{
	if (!this) return;
	AddEffect("IntInvincible", this, 1, 0);
}

global func FxIntInvincibleDamage() { }
