#appendto LavaChunk

private func FxIntEvaporateTimer(object target, proplist effect, int time)
{
	// Some smoke trail.
	Smoke(0, 0, 5);
	Smoke(0, -5, Random(7));
	return 1;
}