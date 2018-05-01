/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:40:14 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/01 17:10:56 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

Window::Window() :  initShape(1),
                    m_width(1280),
                    m_height(1050),
                    m_frameCount(0),
                    m_currTime(0),
                    m_lastTime(SDL_GetTicks()),
                    m_isRunning(true),
                    m_shapeUpdated(false),
                    m_shapeUpdating(false),
                    m_update(true),
                    m_followMouse(true),
                    m_rotate(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
        std::cout << "Init SDL error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Particle System v0.0", SDL_WINDOWPOS_UNDEFINED, \
        SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL);
    if (window == 0)
    {
        std::cout << "Init SDL window error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    GLContext = SDL_GL_CreateContext(window);
    if (GLContext == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    setCamera();
}

Window::~Window()
{
    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), m_width / float(m_height), 0.01f, 1000.0f);
    glm::mat4 View = glm::lookAt(
    glm::vec3(0,0,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    // View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::mat4(1.0f);

    m_project = Projection * View * Model;
    m_project = glm::translate(m_project, glm::vec3(0, 0, -2.0f));
}

void Window::render(CLManager &clManager, ParticleManager &particleManager)
{
    GLuint err;

    while (m_isRunning)
    {
        SDL_PollEvent(&m_event);    
        runKeyCallback();
        runCursorCallback();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // if (m_shapeUpdated)
        // {
        //     clManager.setShape(initShape);
        //     clManager.runInitKernel();
        //     m_shapeUpdated = false;
        //     m_shapeUpdating = true;
        // }
        // else if (clManager.shape == 0)
        // {
        //     m_shapeUpdated = false;
        //     m_shapeUpdating = false;
        //     initShape = 0;
        //     m_update = false;
        //     m_followMouse = false;
        // }
        // if (m_shapeUpdating)
        //     clManager.runInitKernel();
        /*else */
        if (m_update)
        {
            if (m_followMouse)
            {
                // TMP
                particleManager.gravityVec.x = (2.0 * m_mousePosX / 1200 - 1.0);
                particleManager.gravityVec.y = (1.0 - (2.0 * m_mousePosY) / 1080);
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
        SDL_GL_SwapWindow(window);
    }
    // glBindVertexArray(particleManager.m_vao);
    // glBindVertexArray(0);

    // m_program->release();
}

void Window::runCursorCallback()
{
    SDL_GetMouseState(&m_mousePosX, &m_mousePosY);
}

void Window::runKeyCallback()
{
    if (m_event.type == SDL_QUIT)
    {
        m_isRunning = false;
        return ;
    }
    else if (m_event.type == SDL_KEYDOWN)
    {
        switch (m_event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                m_isRunning = false;
                break;
            // case SDLK_SPACE:
            //     m_shapeUpdating = false;
            //     m_update = !m_update;
            //     break;
            case SDLK_c:
                initShape = 1;
                // m_shapeUpdated = true;
                // m_update = true;
                break;
            case SDLK_v:
                initShape = 2;
                // m_shapeUpdated = true;
                // m_update = true;
                break;
            case SDLK_f:
                m_followMouse = !m_followMouse;
                break;
            case SDLK_r:
                m_rotate = !m_rotate;
                break;
            default:;
        }
    }
}
