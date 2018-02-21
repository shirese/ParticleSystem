/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:40:14 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/21 13:29:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Error glfwInit\n");
        return ;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Error glfwCreateWindow\n");
        glfwTerminate();
        return ;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    loadShaders();
    glfwSwapInterval(1);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::loadShaders()
{
    size_t length = 0;
	std::string fragmentShaderSrc, vertexShaderSrc;
	GLuint fs;
	GLuint vs;

    vertexShaderSrc = fileToString(VERTEX_SHADER_SRC);
    fragmentShaderSrc = fileToString(FRAGMENT_SHADER_SRC);
	vs = createShader(vertexShaderSrc, 0);
	fs = createShader(fragmentShaderSrc, 1);
    try
    {
	    if (!checkShader(vs) || !checkShader(fs))
            throw std::bad_exception();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, fs);
	glAttachShader(m_shaderProgram, vs);
	glLinkProgram(m_shaderProgram);
	glDetachShader(m_shaderProgram, fs);
	glDetachShader(m_shaderProgram, vs);
	glUseProgram(m_shaderProgram);
}
