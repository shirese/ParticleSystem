#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>
#include <stdlib.h>
#include <stdio.h>

int check_shader(GLuint shader);
GLuint create_shader(const char *src, int type);

#define VERTEX_SHADER_SRC "/Users/chaueur/ParticleSystem/shaders/vertex_shader.glsl"
#define FRAGMENT_SHADER_SRC "/Users/chaueur/ParticleSystem/shaders/frag_shader.glsl"

#endif // SHADER_H
