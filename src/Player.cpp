//
// Created by lebonq on 23/12/22.
//

#include "Player.hpp"
Player::Player(int map_x, int map_y, float real_x, float real_z, int mapHeight, int mapWidth)
    : CombatEntity(100,0,10), m_real_x(real_x), m_real_z(real_z), m_PosMapX(map_x), m_PosMapY(map_y)
{
    float phi_cam = 0.f;
    int   cam_x   = real_x;
    int   cam_z   = real_z;
    if (cam_z + 1 >= mapHeight)
        phi_cam = 180.f;
    else if (cam_z == 0)
        phi_cam = 0.0f;
    else if (cam_x + 1 >= mapWidth)
        phi_cam = -90.0f;
    else if (cam_x == 0)
        phi_cam = 90.0f;
    this->m_camera = new FreeflyCamera(glm::vec3(cam_x + 1, 0.5, cam_z), phi_cam);
}
Player::~Player()
{
    delete this->m_camera;
}

void Player::moveLevel(int map_x, int map_y, float real_x, float real_z, int mapHeight, int mapWidth){
    float phi_cam = 0.f;
    int   cam_x   = real_x;
    int   cam_z   = real_z;
    if (cam_z + 1 >= mapHeight)
        phi_cam = 180.f;
    else if (cam_z == 0)
        phi_cam = 0.0f;
    else if (cam_x + 1 >= mapWidth)
        phi_cam = -90.0f;
    else if (cam_x == 0)
        phi_cam = 90.0f;
    this->m_camera->setPosition(glm::vec3(cam_x + 1, 0.5, cam_z));
    this->m_camera->setPhi(phi_cam);
    this->updateRealPos();
    this->updateMapPos();
}

void Player::update()
{
    if(this->getLife() <= 0){
        this->m_dead = true;
    }
}

void Player::moveToLeftCamera(double distance)
{
    this->m_camera->moveLeft(distance);
    this->updateRealPos();
}

void Player::updateMapPos()
{
    this->m_PosMapX = static_cast<int>(this->m_real_x)-1;
    this->m_PosMapY = static_cast<int>(this->m_real_z);
}

void Player::updateRealPos()
{
    this->m_real_x = round(static_cast<float>(this->m_camera->getPosition().x));
    this->m_real_z = round(static_cast<float>(this->m_camera->getPosition().z));
}

void Player::moveToFrontCamera(double distance)
{
    this->m_camera->moveFront(distance);
    this->updateRealPos();
}

void Player::rotateLeftCamera(double angle)
{
    this->m_camera->rotateLeft(angle);
    glm::vec3 frontVec = this->getCamera()->getFrontVector();
    this->m_xLookAt     = round(frontVec.x);
    this->m_yLookAt      = round(frontVec.z);
}
float Player::getXLookAt() const
{
    return m_PosMapX + m_xLookAt;
}
float Player::getYLookAt() const
{
    return m_PosMapY +m_yLookAt;
}
float Player::getLookAtXValue() const
{
    return m_xLookAt;
}
float Player::getLookAtYValue() const
{
    return m_yLookAt;
}
