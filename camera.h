/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:50:46 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/18 14:38:46 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H

#define CAMERA_H

#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
// #include <glm/gtx/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

class Camera
{
    public:
        Camera();
        ~Camera();
        void update();
        glm::mat4 getProject() { return (m_project); };
        void translate(glm::vec3 vecTranslate);

    private : 
        glm::mat4 m_project;
        glm::vec3 m_position;
        glm::vec3 m_positionDelta;
        glm::vec3 m_lookDir;
        glm::vec3 m_lookAt;
        glm::vec3 m_upDir;
        float m_headAngle;
        float m_pitch;
        float m_fov;
        float m_nearPlane, m_farPlane;
        float m_aspectRatio;
};

#endif
