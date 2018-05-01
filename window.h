/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:36:16 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/01 14:23:50 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H

#define WINDOW_H

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
#include <SDL.h>

class Window
{

public:
  Window();
  ~Window();
  void loadShaders();
  void setCamera();
  void render(CLManager &clManager, ParticleManager &particleManager);
  void runKeyCallback();
  void runCursorCallback();
  SDL_GLContext GLContext;
  SDL_Window *window;
  GLuint shaderProgram;
  short initShape;

private:
  unsigned int m_width;
  unsigned int m_height;
  int m_frameCount;
  double m_currTime;
  double m_lastTime;
  int m_mousePosX, m_mousePosY;
  SDL_Event m_event;
  bool m_isRunning;
  bool m_shapeUpdated;
  bool m_shapeUpdating;
  bool m_update;
  bool m_followMouse;
  bool m_rotate;
  glm::mat4 m_project;
};

#endif
