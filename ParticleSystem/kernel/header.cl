#define GRAV_RADIUS 0.1f
#define PARTICLES_COUNT 1024000
#define SQUARE_SIZE		1.0f
#define SPHERE_RADIUS	1.f
#define G 9.81f
#define ATTRACT (G * 0.01f * 4.0f)

typedef struct
{
	float3	position;
	float3	color;
	float3	velocity;
}			Particle;
