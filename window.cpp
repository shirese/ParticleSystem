/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:40:14 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/22 19:25:44 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

Window::Window() : initShape(1),
                   m_shapeUpdated(false),
                   m_shapeUpdating(false),
                   m_update(true),
                   m_followMouse(true),
                   m_rotate(false)
{
    if (!glfwInit())
    {
        fprintf(stderr, "Error glfwInit\n");
        return;
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
        return;
    }
    setCamera();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::loadShaders()
{
    std::string fragmentShaderSrc, vertexShaderSrc;
    GLuint fs;
    GLuint vs;

    vertexShaderSrc = fileToString(VERTEX_SHADER_SRC);
    fragmentShaderSrc = fileToString(FRAGMENT_SHADER_SRC);
    try
    {
        if (!(vs = createShader(vertexShaderSrc, 0)))
            throw std::bad_exception();
        if (!(fs = createShader(fragmentShaderSrc, 1)))
            throw std::bad_exception();
        if (!checkShader(vs) || !checkShader(fs))
            throw std::bad_exception();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    glDetachShader(shaderProgram, fs);
    glDetachShader(shaderProgram, vs);
    glUseProgram(shaderProgram);
}

void Window::setCamera()
{
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    // View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::mat4(1.0f);

    m_project = Projection * View * Model;
}

void Window::render(CLManager &clManager, ParticleManager &particleManager)
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLuint err;
        if (m_shapeUpdated)
        {
            clManager.setShape(initShape);
            clManager.runInitKernel();
            m_shapeUpdated = false;
            m_shapeUpdating = true;
        }
        else if (clManager.shape == 0)
        {
            m_shapeUpdated = false;
            m_shapeUpdating = false;
            initShape = 0;
            m_update = false;
            m_followMouse = false;
        }
        if (m_shapeUpdating)
            clManager.runInitKernel();
        else if (m_update)
        {
            if (m_followMouse)
            {
                // TMP
                particleManager.gravityVec.x = (2.0 * m_mousePosX / 640 - 1.0);
                particleManager.gravityVec.y = (1.0 - (2.0 * m_mousePosY) / 480);
                particleManager.gravityVec.z = 0;
                // m_gravityVec.setZ(0);
            }
            float *grav = hitPlane(particleManager.gravityVec, 2);
            clManager.runUpdateKernel(grav);
            delete grav;
        }
        glUniformMatrix4fv(particleManager.getMatrixUniform(), 1, GL_FALSE, &m_project[0][0]);
        glBindVertexArray(particleManager.getVAO());
        glDrawArrays(GL_POINTS, 0, PARTICLES_COUNT);
	    glBindVertexArray(0);
        err = glGetError();
        if (err != GL_NO_ERROR)
            printf("Error: OpenGL Get Error: %d\n", err);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glBindVertexArray(particleManager.m_vao);
    // glBindVertexArray(0);

    // m_program->release();
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    void *data = glfwGetWindowUserPointer(window);
    Window *w = static_cast<Window *>(data);
    switch (key)
    {
    case GLFW_KEY_SPACE:
        w->m_update = !w->m_update;
        w->m_shapeUpdating = false;
        break;
    case GLFW_KEY_C:
        w->initShape = 1;
        w->m_shapeUpdated = true;
        w->m_update = true;
        break;
    case GLFW_KEY_V:
        w->initShape = 2;
        w->m_shapeUpdated = true;
        w->m_update = true;
        break;
    case GLFW_KEY_F:
        w->m_followMouse = !w->m_followMouse;
        break;
    case GLFW_KEY_R:
        w->m_rotate = !w->m_rotate;
        break;
    default:;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::cursorCallback(GLFWwindow *window, double xpos, double ypos)
{
    void *data = glfwGetWindowUserPointer(window);
    Window *w = static_cast<Window *>(data);

    w->m_mousePosX = xpos;
    w->m_mousePosY = ypos;
}
