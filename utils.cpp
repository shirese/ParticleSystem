/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:40:44 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/21 13:26:58 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

std::string fileToString(const char *file_name)
{
	std::ifstream in(file_name);
	std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	return (s);
}

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
    const char *c_str;

    if (type == 0)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    c_str = str.c_str();
    glShaderSource(shader, 1, &(c_str), NULL);
    glCompileShader(shader);
    return (shader);
}
