/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:40:54 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/22 17:41:39 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <OpenGL/gl3.h>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <stdio.h>
# include <sys/stat.h>

# include <glm/glm.hpp>
# include <glm/vec3.hpp> // glm::vec3

# define VERTEX_SHADER_SRC "/Users/chaueur/ParticleSystem/shaders/vertex_shader.glsl"
# define FRAGMENT_SHADER_SRC "/Users/chaueur/ParticleSystem/shaders/frag_shader.glsl"

std::string fileToString(const char *file_name);
int checkShader(GLuint shader);
GLuint createShader(std::string str, int type);
float *hitPlane(glm::vec3 origin, float d);

#endif // UTILS_H
