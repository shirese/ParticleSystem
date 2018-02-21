/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:40:54 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/21 13:03:51 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <cstdlib>
# include <fstream>
# include <iostream>
# include <stdio.h>
# include <sys/stat.h>
# include <OpenGL/gl.h>

# define VERTEX_SHADER_SRC "/Users/chaueur/ParticleSystem/ParticleSystem/shaders/vertex_shader.glsl"
# define FRAGMENT_SHADER_SRC "/Users/chaueur/ParticleSystem/ParticleSystem/shaders/frag_shader.glsl"

std::string fileToString(const char *file_name);
int checkShader(GLuint shader);
GLuint createShader(std::string str, int type);

#endif // UTILS_H
