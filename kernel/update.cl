// float3 getParticleColor(float dist, float3 particlePosition)
// {
// 	float3 color;

// 	dist *= 0.25f;
// 	color.x = 1 - dist;
// 	color.y = 0.0;
// 	color.z = dist;
// 	return (color);
// }

void kernel update_position(__global Particle *particles, __constant float3 *gravityCenter)
{
	int					i = get_global_id(0);
	float				dist;
	float				force;

	particles += i;
	dist = distance(*gravityCenter, particles->position);
	if (dist <= GRAV_RADIUS)
		return ;
	force = ATTRACT / (dist * dist);
	particles->velocity += (*gravityCenter - particles->position) * force;
	particles->position += particles->velocity;
	dist *= 0.42f;
	particles->color.x = 1 - dist;
	particles->color.z = dist;
	// getParticleColor(dist, particles->position);
	particles->velocity *= 0.8f;
}
