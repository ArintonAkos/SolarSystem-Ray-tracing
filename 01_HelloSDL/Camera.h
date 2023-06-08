#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera {
private:
    glm::vec3 m_eye, m_at, m_up;
    float m_speed;
    float m_goFw, m_goRight;
    float m_dist;
    bool m_slow;
    glm::vec3 m_fw, m_st;
    float m_u, m_v;
    glm::mat4 m_matProj, m_matViewProj, m_viewMatrix;

    void UpdateUV(float du, float dv);
    void SetView(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up);
    void SetProj(float _angle, float _aspect, float _zn, float _zf);

    static int last_mouse_x;
    static int last_mouse_y;

public:
    Camera(glm::vec3 _eye, glm::vec3 _at, glm::vec3 _up);
    ~Camera(void);

    glm::mat4 GetViewMatrix();
    void Update(float _deltaTime);
    void SetSpeed(float _val);
    void Resize(int _w, int _h);

    void KeyboardDown(SDL_KeyboardEvent& key);
    void KeyboardUp(SDL_KeyboardEvent& key);
    void MouseMove(SDL_MouseMotionEvent& mouse);

    glm::vec3 GetEye() { return m_eye; }
    glm::vec3 GetAt() { return m_at; }
    glm::vec3 GetUp() { return m_up; }
    glm::mat4 GetProj() { return m_matProj; }
    glm::mat4 GetViewProj() { return m_matViewProj; }

    SDL_Rect getView();
};