//
// Created by lebonq on 23/12/22.
//

#include "Player.hpp"
Player::Player(Model* model, glm::mat4 mat, int map_x, int map_y, float real_x, float real_z)
    : InteractiveObject(model, mat, map_x, map_y), m_real_x(real_x), m_real_z(real_z)
{
}
Player::~Player()
{

}
void Player::update()
{
}
void Player::getClicked()
{
}

void Player::draw()
{
    //We don't draw the player
}
