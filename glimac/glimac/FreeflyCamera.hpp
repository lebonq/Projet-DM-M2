//
// Created by lebonq on 16/12/22.
//
#ifndef SIMPLEGLIMAC_FREEFLYCAMERA_HPP
#define SIMPLEGLIMAC_FREEFLYCAMERA_HPP

#include <glimac/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class FreeflyCamera {
private:
    glm::vec3 m_Position, m_FrontVector, m_LeftVector, m_UpVector;
    float     m_fPhi, m_fTheta;

    void computeDirectionVectors()
    {
        this->m_FrontVector = glm::vec3(glm::cos(m_fTheta) * glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta) * glm::cos(m_fPhi));
        this->m_LeftVector  = glm::vec3(glm::sin(this->m_fPhi + ( M_PI / 2)), 0, glm::cos(this->m_fPhi + (M_PI / 2)));
        this->m_UpVector    = glm::cross(this->m_FrontVector, this->m_LeftVector);
    };

public:
    /**
     * Place the camera
     * @param pos_cam
     * @param phi Where the camera look
     */
    FreeflyCamera(glm::vec3 pos_cam, float phi)
    {
        this->m_Position = pos_cam;
        this->m_fPhi     = glm::radians(phi);
        this->m_fTheta   = glm::radians(0.0f);
        computeDirectionVectors();
    };
    FreeflyCamera()
        : FreeflyCamera(glm::vec3(1, 0.5, 0),static_cast<float>(M_PI) * 2) {}
    ~FreeflyCamera(){

    };

    void moveLeft(const float t)
    {
        this->m_Position += t * this->m_LeftVector;
    };

    void moveFront(const float t)
    {
        this->m_Position += t * this->m_FrontVector;
    };

    void rotateLeft(const float degrees)
    {
        float radian = glm::radians(degrees);
        this->m_fPhi += radian;
        computeDirectionVectors();
    };

    void rotateUp(const float degrees)
    {
        float radian = glm::radians(degrees);
        this->m_fTheta += radian;
        computeDirectionVectors();
    };

    glm::vec3 getFrontVector()
    {
        return m_FrontVector;
    }

    glm::vec3 getPosition()
    {
        return m_Position;
    }

    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(this->m_Position, this->m_Position + this->m_FrontVector, this->m_UpVector);
    };

    void setPhi(float phi){
        this->m_fPhi = glm::radians(phi);
        computeDirectionVectors();
    }

    void setPosition(glm::vec3 pos){
        this->m_Position = pos;
    }
};

#endif // SIMPLEGLIMAC_FREEFLYCAMERA_HPP
