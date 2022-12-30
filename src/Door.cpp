//
// Created by lebonq on 23/12/22.
//

#include "Door.hpp"

Door::Door(Model* model, const glm::mat4& mat, int mapX, int mapY, int price)
    : InteractiveObject(model, nullptr, mat, mapX, mapY), m_price(price)
{
}
bool Door::getClicked(Player* player, std::string& message, bool* printMessage)
{
    if (player->getGold() >= this->m_price && !this->m_paid) {
        player->changeGold(-this->m_price);
        this->m_open     = true;
        this->m_paid     = true;
        this->m_Animated = true;
        this->m_moveDirection = 1;
        message = "Door Opened";
        *printMessage = true;
        DEBUG_PRINT("Door opended" << std::endl);
    }
    //si on a paye la porte et qu'elle n'est pas actuellement animée on l'ouvre ou la ferme
    else if(this->m_paid && !this->m_Animated) {
        if (this->m_open) {
            this->m_Animated      = true;
            this->m_open          = false;
            this->m_moveDirection = -1;
            DEBUG_PRINT("Door closed" << std::endl);
        }
        else {
            this->m_Animated      = true;
            this->m_open          = true;
            this->m_moveDirection = 1;
            DEBUG_PRINT("Door opened" << std::endl);
        }
    }
    else if(!this->m_paid){
        *printMessage = true;
        message = "Cannot not open. Price is " + std::to_string(this->m_price);
    }
    return false;
}
void Door::draw()
{
    InteractiveObject::draw();
}
void Door::update(double current_time)
{
    if (this->m_Animated) {
        double move_distance = ((current_time - this->m_previousTime)*0.8) / 1700;
        this->m_doneMove += static_cast<float>(move_distance);
        this->m_doneMove_real += static_cast<float>(move_distance);
        this->m_doneMove = glm::clamp(this->m_doneMove, 0.0f, 0.80f);
        if (this->m_doneMove == 0.8f) {
            float     move_distancef = -(this->m_doneMove_real - static_cast<float>(move_distance)) + 0.80f;
            glm::mat4 mmatrix = this->m_MMatrix;
            this->m_currentAltitude += move_distancef*static_cast<float>(this->m_moveDirection);
            mmatrix = glm::translate(mmatrix, glm::vec3(0.f, this->m_currentAltitude, 0.f));
            this->updateModelMatrix(mmatrix);
            this->m_Animated = false;
            this->m_doneMove      = 0;
            this->m_doneMove_real = 0;
        }
        else {
            this->m_currentAltitude += move_distance*this->m_moveDirection;
            glm::mat4 mmatrix = this->m_MMatrix;
            mmatrix = glm::translate(mmatrix, glm::vec3(0,  this->m_currentAltitude,0));//fix door TODO
            this->updateModelMatrix(mmatrix);
        }
    }
    this->m_previousTime = current_time;
}
