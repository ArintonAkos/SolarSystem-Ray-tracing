#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class Camera {
private:
    glm::vec3 eye, worldUp;
    glm::vec3 frontAxis, sideAxis, upAxis;
    glm::mat4 projectionMatrix, viewMatrix, viewProjectionMatrix;

    float yaw, pitch;
    float speed, sensitivity;
    float moveForward, moveRight, moveUp;
    
    void calculateViewMatrix();
  
    void setViewMatrix(glm::vec3 eye, glm::vec3 worldUp, float pitch, float yaw);
    void setProjectionMatrix(float angle, float aspect, float zn, float zf);

public:
    Camera(glm::vec3 eye, glm::vec3 worldUp, float pitch, float yaw);
    ~Camera();

    void setSpeed(float value);

    glm::vec3 getEyePosition() const;
    glm::vec3 getForwardDirection() const;
    glm::vec3 getUpDirection() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;
    
    void update(float deltaTime);
    void updateView(float relPitch, float relYaw);

    void resize(int width, int height);

    void handleKeyDownEvent(const SDL_KeyboardEvent& key);
    void handleKeyUpEvent(const SDL_KeyboardEvent& key);
    void handleMouseMovedEvent(const SDL_MouseMotionEvent& mouse);
};