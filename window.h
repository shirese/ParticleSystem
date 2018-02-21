/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:36:16 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/21 13:08:21 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "utils.h"

class Window
{
  public:
    Window();
    ~Window();
    void loadShaders();

    GLFWwindow *window;

  
  private:
    GLuint m_shaderProgram;
};

#endif
