float3 getParticleColor(float dist, float3 particlePosition)
{
	float3 color;

	color.x = 1 - dist/4.;
	color.y = 0.0;
	color.z = dist/4.;
	return (color);
}

void kernel update_position(__global Particle *particles, __global float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	const float			minGravityDist = 0.25;
	float3				dd;
	float				force;

	dd = *gravityCenter - particles[i].position;
	dist = distance(*gravityCenter, particles[i].position);
	if (dist <= minGravityDist)
		return ;
	force = (G * 0.01 * 4) / (pow(dist, 2));
	particles[i].velocity += dd * (float3)force;
	particles[i].position += particles[i].velocity;
	particles[i].color = getParticleColor(dist, particles[i].position);
	particles[i].velocity *= 0.8f;
}
