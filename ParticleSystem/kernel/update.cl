float3 getParticleColor(float dist, float3 particlePosition)
{
	float3 color;

	dist *= 0.25f;
	color.x = 1 - dist;
	color.y = 0.0;
	color.z = dist;
	return (color);
}

void kernel update_position(__global Particle *particles, __global float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	const float			minGravityDist = 0.25;
	float3				dd;
	float				force;
	const float			test = (G * 0.01 * 4);

	particles += i;
	dd = *gravityCenter - particles->position;
	dist = distance(*gravityCenter, particles->position);
	if (dist <= minGravityDist)
		return ;
	force = test / (dist * dist);
	particles->velocity += dd * (float3)force;
	particles->position += particles->velocity;
	particles->color = getParticleColor(dist, particles->position);
	particles->velocity *= 0.8f;
}
