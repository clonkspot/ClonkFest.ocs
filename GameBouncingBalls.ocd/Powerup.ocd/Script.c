/*--
	Powerup
	Author: Sven2

	Collectible powerup in BouncingBalls game
--*/

/*-- Initialize --*/

local ring_particle, radius, active, powerup;

public func Initialize()
{
	ring_particle =
	{
		Size = PV_KeyFrames(0, 0, 0, 250, 10, 500, 0, 750, 10),
		Alpha = PV_KeyFrames(0, 0, 255, 500, 0, 501, 255, 1000, 0),
		R = 255, G = 0, B = 0,
		BlitMode = GFX_BLIT_Additive,
		Attach = ATTACH_Front
	};
	AddEffect("IntPowerupCreation", this, 100, 2, this);
	AddEffect("IntPowerup", this, 100, 2, this);
	return;
}


/*-- Timer --*/

private func FxIntPowerupCreationTimer(object target, effect, int fxtime)
{
	radius = Min(fxtime/2, 13);
	if (fxtime >= 70)
	{
		active = true;
		var valid_powerups = [Sproutberry, WallKit, Skull];
		powerup = valid_powerups[Random(GetLength(valid_powerups))];
		CreateParticle("Flash", 0, 0, 0, 0, 32, Particles_Flash(60));
		Sound("UI::Open");
		SetGraphics(nil, powerup, 1, GFXOV_MODE_IngamePicture);
		return FX_Execute_Kill;
	}
	return FX_OK;
}

private func FxIntPowerupTimer(object target, effect, int fxtime)
{
	// Collection check
	if (active)
	{
		var ball = FindObject(Find_AtPoint(), Find_ID(BouncingBall), Find_OCF(OCF_Alive), Sort_Distance());
		if (ball)
		{
			DoPowerup(ball, powerup);
			var game = FindObject(Find_ID(Game_S2BouncingBalls));
			if (game) game->SchedulePowerup();
			RemoveObject();
			return FX_Execute_Kill;
		}
	}
	// Graphics
	var angle = (fxtime * 10) % 360;
	CreateParticle("SphereSpark", Sin(angle, radius), -Cos(angle, radius), 0, 0, 18 * 5, ring_particle);
	return FX_OK;
}


/* Powerup collection */

private func DoPowerup(ball, powerup)
{
	CreateParticle("Flash", 0, 0, 0, 0, 12, Particles_Flash(70));
	ball->Sound("UI::Cleared");
	Call(Format("Powerup_%i", powerup), ball);
}


/* Invulnerability (Sproutberry) powerup */
// Stolen from Knueppeln by Kenny

private func Powerup_Sproutberry(ball)
{
	ball->Sound("BouncingBalls_Powerup::superberry?", false, 50, nil, +1);
	AddEffect("Superberry", ball, 1, 1, nil, GetID());
	return true;
}

private func FxSuperberryStart(object target, effect, int temporary)
{
	target.max_accel += 10;
}

private func FxSuperberryTimer(target, fx, timer)
{
	if (timer > 40*5) return FX_Execute_Kill;

	var rgba = SplitRGBaValue(HSL(Random(255), 255, 128));
	
	var props = {
		R = rgba[0],
		G = rgba[1],
		B = rgba[2],
		Size = PV_Linear(5, 0),
		Alpha = PV_Linear(255,0),
		OnCollision = PC_Bounce(),
		ForceY = PV_Gravity(200),
		BlitMode = GFX_BLIT_Additive
	};
	
	target->CreateParticle("StarSpark", PV_Random(-5, 5), PV_Random(-10, 10), PV_Random(-4,4), PV_Random(-20, -5), 20, props, 1);
	
	target->SetClrModulation(HSL(timer*20, 255, 128));
}

private func FxSuperberryDamage()
{
	return 0;
}

func FxSuperberryStop(object target, proplist fx, int reason, bool temporary)
{
	target.max_accel -= 10;
	if (!temporary)
	{
		target->SetClrModulation(RGB(255,255,255));
		target->Sound("BouncingBalls_Powerup::superberry?", false, 50, nil, -1);
	}
	return FX_OK;
}


/* WallKit powerup: Launch a few walls */

private func Powerup_WallKit(ball)
{
	// Walls in all directions
	var game = FindObject(Find_ID(Game_S2BouncingBalls));
	if (game) for (var i=0; i<3; ++i) game->LaunchWall(i);
	return true;
}


/* Skull powerup: Particles change direction towards other players */

private func Powerup_Skull(ball)
{
	var targets = FindObjects(Find_ID(BouncingBall), Find_Exclude(ball), Find_OCF(OCF_Alive));
	var n_targets = GetLength(targets), i;
	if (!n_targets) targets[n_targets++] = ball; // no other players? Tough luck, all go towards this player...
	for (var rock in FindObjects(Find_ID(FireRock)))
	{
		var target = targets[i++ % n_targets];
		if (target)
		{
			rock->Launch(target->GetX(), target->GetY());
		}
	}
	return true;
}


/*-- Proplist --*/

local Name = "$Name$";
local Description = "$Description$";


