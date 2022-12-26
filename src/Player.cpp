//
// Created by lebonq on 23/12/22.
//

#include "Player.hpp"
Player::Player(int map_x, int map_y, float real_x, float real_z, int mapHeight, int mapWidth)
    : m_real_x(real_x), m_real_z(real_z), m_PosMapX(map_x), m_PosMapY(map_y)
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
}
void Player::update()
{
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
