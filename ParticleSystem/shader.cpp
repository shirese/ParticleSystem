#include "shader.h"

int check_shader(GLuint shader)
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
        printf("%s\n", log);
        free(log);
        return (0);
    }

    return (1);
}

GLuint create_shader(const char *src, int type)
{
    GLuint shader;

    if (type == 0)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return (shader);
}
