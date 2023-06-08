#include "Camera.h"
#include <SDL.h>
#include <iostream>

Camera::Camera(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up) : m_eye(_eye), m_at(_at), m_up(_up) 
{
    m_speed = 16.0f;
    m_goFw = m_goRight = 0;
    m_dist = 10;
    m_slow = false;

    SetView(_eye, _at, _up);
    SetProj(glm::radians(60.0f), 640 / 480.0f, 0.01f, 1000.0f);
}

Camera::~Camera(void) {}

void Camera::UpdateUV(float du, float dv) 
{
    m_u += du;
    m_v = glm::clamp<float>(m_v + dv, 0.1f, 3.1f);

    m_at = m_eye + m_dist * glm::vec3(cosf(m_u) * sinf(m_v),
        cosf(m_v),
        sinf(m_u) * sinf(m_v));

    m_fw = glm::normalize(m_at - m_eye);
    m_st = glm::normalize(glm::cross(m_fw, m_up));
}

void Camera::SetView(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up) 
{
    m_eye = _eye;
    m_at = _at;
    m_up = _up;

    m_fw = glm::normalize(m_at - m_eye);
    m_st = glm::normalize(glm::cross(m_fw, m_up));

    m_dist = glm::length(m_at - m_eye);

    m_u = atan2f(m_fw.z, m_fw.x);
    m_v = acosf(m_fw.y);
}

void Camera::SetProj(float _angle, float _aspect, float _zn, float _zf) 
{
    m_matProj = glm::perspective(_angle, _aspect, _zn, _zf);
    m_matViewProj = m_matProj * m_viewMatrix;
}

glm::mat4 Camera::GetViewMatrix() 
{
    return m_viewMatrix;
}

void Camera::Update(float _deltaTime)
{
    if (m_goFw || m_goRight) {
        glm::vec3 direction = (m_goFw * m_fw + m_goRight * m_st);
        direction = glm::normalize(direction);
        glm::vec3 move = direction * m_speed * _deltaTime;

        m_eye += move;
        m_at += move;

        m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
        m_matViewProj = m_matProj * m_viewMatrix;
    }
}

void Camera::SetSpeed(float _val)
{
    m_speed = _val;
}

void Camera::Resize(int _w, int _h)
{
    SetProj(glm::radians(60.0f), _w / (float)_h, 0.01f, 1000.0f);
}

void Camera::KeyboardDown(SDL_KeyboardEvent& key)
{
    // Implement your KeyboardDown logic here
}

void Camera::KeyboardUp(SDL_KeyboardEvent& key)
{
    // Implement your KeyboardUp logic here
}

void Camera::MouseMove(SDL_MouseMotionEvent& mouse)
{
    // Implement your MouseMove logic here
}