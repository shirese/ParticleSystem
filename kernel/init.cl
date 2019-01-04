void kernel initialize(__global Particle *particles, __global short *shape)
{
	int i = get_global_id(0);
	float3 dir;

	particles += i;
	particles->color.x = 0.18;
	particles->color.y = 0.12;
	particles->color.z = 0.65;
	if (*shape == 1)
	{
		float theta = GA * (float)i;
		float z = Z_HELPER * ( 1.0 - ( (2. * (float)i) / ( (float)PARTICLES_COUNT - 1.0 ) ) );
		float radius = sqrt(1.0 - z * z);
		dir.x = radius * cos(theta);
		dir.y = radius * sin(theta);
		dir.z = z;
		dir = particles->position - dir;
		particles->position = (float3)0.6 * dir;
	}
	else if (*shape == 2)
	{
		uint	subDivCount = cbrt((float)PARTICLES_COUNT);
		uint	x = fmod((float)i, (float)subDivCount);
		uint	y = fmod((float)i / subDivCount, (float)subDivCount);
		uint	z = i / (subDivCount * subDivCount);
		float	subDivSize = SQUARE_SIZE / subDivCount;
		float	subDivSize2 = subDivSize / 2.0f;
		dir.x = x * subDivSize - 0.5 + subDivSize2;
		dir.y = y * subDivSize - 0.5 + subDivSize2;
		dir.z = z * subDivSize - 0.5 + subDivSize2;
		dir = particles->position - dir;
		particles->position = (float3)0.6 * dir;
	}
}
