/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:33:11 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/21 12:35:43 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/OpenGL.h>
#include <cstdlib>
#include <stdio.h>

int checkShader(GLuint shader)
{
    GLint success;
    int log_size;
    char *log;

    log = nullptr;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    if (!success)
    {
        glGetShaderInfoLog(shader, log_size, nullptr, &log[0]);
        fprintf(stderr, "%s\n", log);
        free(log);
        return (0);
    }

    return (1);
}

GLuint createShader(std::string str, int type)
{
    GLuint shader;

    if (type == 0)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, str.c_str(), NULL);
    glCompileShader(shader);
    return (shader);
}
