/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:40:44 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/23 12:25:45 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

std::string fileToString(const char *file_name)
{
    std::ifstream ifs(file_name);
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    return (content);
}

int checkShader(GLuint shader)
{
    GLint success;
    int logsize;
    char *log;

    log = nullptr;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        log = (char *)malloc(logsize + 1);
        if (log == NULL)
        {
            fprintf(stderr, "Log malloc error.\n");
            return 0;
        }
        memset(log, '\0', logsize + 1);
        glGetShaderInfoLog(shader, logsize, &logsize, log);
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

    if (str.empty())
        return (0);
    if (type == 0)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!shader)
        return (0);
    c_str = str.c_str();
    glShaderSource(shader, 1, &(c_str), NULL);
    glCompileShader(shader);
    return (shader);
}

float *hitPlane(glm::vec3 origin, float d)
{
    glm::vec3 direction(origin.x, origin.y, -1);
    glm::vec3 planeOrigin(0, 0, -2);
    glm::vec3 planeNormal(0, 0, 1);
    glm::vec3 ret;
    float t;
    float *p;

    t = glm::dot(planeOrigin - origin, planeNormal) / glm::dot(planeNormal, direction);
    if (t >= 0.0001)
    {
        ret = origin + t * direction;
        p = new float[3];
        p[0] = ret.x;
        p[1] = ret.y;
        p[2] = ret.z;
        return (p);
    }
    return (0);
}
