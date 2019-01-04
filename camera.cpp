/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:53:36 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/18 14:42:55 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

Camera::Camera() :  m_position(glm::vec3(0, 0, 1)),
                    m_lookDir(glm::vec3(0, 0, 0)),
                    m_upDir(glm::vec3(0, 1, 0)),
                    m_fov(60),
                    m_nearPlane(0.01f),
                    m_farPlane(1000.0f),
                    m_aspectRatio(1920.0f / 1080.0f)
{
    glm::mat4 Projection = glm::perspective(
        glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
    glm::mat4 View = glm::lookAt(
        m_position, // Camera is at (4,3,3), in World Space
        m_lookDir, // and looks at the origin
        m_upDir  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    // View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::mat4(1.0f);

    m_project = Projection * View * Model;
    m_project = glm::translate(m_project, glm::vec3(0, 0, -2.0f));
}

Camera::~Camera()
{
}

void Camera::update()
{
    glm::mat4 Projection = glm::perspective(
        glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
    glm::mat4 View = glm::lookAt(
        m_position, // Camera is at (4,3,3), in World Space
        m_lookDir,  // and looks at the origin
        m_upDir     // Head is up (set to 0,-1,0 to look upside-down)
    );
    // View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    // View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::mat4(1.0f);

    m_project = Projection * View * Model;
    m_project = glm::translate(m_project, glm::vec3(0, 0, -2.0f));
}

void Camera::translate(glm::vec3 vecTranslate)
{
    m_position += vecTranslate;
}
