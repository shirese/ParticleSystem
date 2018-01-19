#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl.h>
#include <stdlib.h>
#include <stdio.h>

int check_shader(GLuint shader);
GLuint create_shader(const char *src, int type);

#define VERTEX_SHADER_SRC "/Users/chaueur/ParticleSystem/ParticleSystem/shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER_SRC "/Users/chaueur/ParticleSystem/ParticleSystem/shaders/frag_shader.glsl"

#endif // SHADER_H
