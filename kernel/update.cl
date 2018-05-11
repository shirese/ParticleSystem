// float3 getParticleColor(float dist, float3 particlePosition)
// {
// 	float3 color;

// 	dist *= 0.25f;
// 	color.x = 1 - dist;
// 	color.y = 0.0;
// 	color.z = dist;
// 	return (color);
// }

void kernel update_position(__global Particle *particles, __constant float2 *gravityCenter)
{
	int					i = get_global_id(0);
	float				r;
	float				force;
	float				orbital_speed;
	float3				gc;
	float3				dir;

	particles += i;
	gc = (float3)(*gravityCenter, 0.0);
	dir = (gc - particles->position);	
	r = fast_length(dir);
	if (r <= GRAV_RADIUS)
	{
		particles->velocity += (float3)0.01f;
		particles->position += particles->velocity;
		return ;
	}
	// fast_normalize(dir);
	// fast_normalize(dir);
	force = ATTRACT / (r * r);
	// if (force > 4.0f)
	// 	particles->velocity *= (float3)0.001f * force;	
	if (!particles->velocity.x)
		particles->velocity = float3(0.0001f, 0.0001f, 0);
	float tmp = fast_length(dir);
	if (tmp > 1.5f)
		particles->position = gc;
	// else
	// {
	// 	orbital_speed = sqrt((0.24f * G) / r);
	// 	particles->velocity *= (float3)orbital_speed;
	// }
	particles->velocity += dir * force;
	float len = fast_length(particles->velocity);
	if (len > 0.2f)
		particles->velocity *= (float3)0.00001f * force;
	particles->position += particles->velocity;
	// particles->velocity *= (float3)0.4;
	// particles->position += -dir * force;
	// dist *= 0.42f;
	particles->color.z = (len - 0.015591) / 0.091556;
	particles->color.x = tmp * 0.75f;
	// particles->color.x = clamp(particles->color.x, 0.2f, 0.8f);
	// getParticleColor(dist, particles->position);
	// particles->velocity *= 0.8f;
}
