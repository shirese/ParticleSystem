#define GRAV_RADIUS 0.1f
#define PARTICLES_COUNT 1024000
#define SQUARE_SIZE		5.0f
#define SPHERE_RADIUS	10.0f
#define G 9.81f
#define ATTRACT (G * 0.01f * 4.0f)

typedef struct
{
	float3	position;
	float3	color;
}			Particle;
