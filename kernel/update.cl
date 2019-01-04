void kernel update_position(__global Particle *particles, __constant float2 *gravityCenter)
{
	int					i = get_global_id(0);
	float				r;
	float				force;
	float3				gc;
	float3				dir;

	particles += i;
	gc = (float3)(*gravityCenter, 0.0);
	dir = (gc - particles->position);	
	r = fast_length(dir);
	if (r <= GRAV_RADIUS)
	{
		particles->velocity += (float3)0.00001f;
		particles->position += particles->velocity;
		return ;
	}
	force = ATTRACT / (r * r);
	float tmp = fast_length(dir);
	if (tmp > 1.5f)
		particles->position = gc;
	particles->velocity += dir * force;
	float len = fast_length(particles->velocity);
	if (len > 0.2f)
		particles->velocity *= (float3)0.00001f * force;
	particles->position += particles->velocity;
	particles->color.x = tmp * 0.75f;
	particles->color.y = 0.38 * fabs(fast_length((float3)(gravityCenter->x, gravityCenter->y, 1.0f) - particles->position));
	particles->color.z = (len - 0.015591) / 0.091556;
}
