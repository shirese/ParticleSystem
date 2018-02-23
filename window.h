/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:36:16 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/23 15:08:31 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H

#define WINDOW_H

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "clmanager.h"
#include "particlemanager.h"
#include "particle.h"
#include "utils.h"

#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

class Window
{

public:
  Window();
  ~Window();
  void loadShaders();
  void setCamera();
  void render(CLManager &clManager, ParticleManager &particleManager);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void cursorCallback(GLFWwindow *window, double xpos, double ypos);
  GLFWwindow *window;
  GLuint shaderProgram;
  short initShape;

private:
  int m_frameCount;
  double m_currTime;
  double m_lastTime;
  double m_mousePosX, m_mousePosY;
  bool m_shapeUpdated;
  bool m_shapeUpdating;
  bool m_update;
  bool m_followMouse;
  bool m_rotate;
  glm::mat4 m_project;
};

#endif
