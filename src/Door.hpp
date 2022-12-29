//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_DOOR_HPP
#define PROJET_DM_QUENTIN_LEBON_DOOR_HPP

#include "InteractiveObject.hpp"
class Door : public InteractiveObject{
public:
    Door(Model* model,  const glm::mat4& mat, int mapX, int mapY, int price);
    bool getClicked(Player* player) override;
    void draw() override;
    void update(double current_time);
    bool isOpen() const
    {
        return m_open;
    };

private:
    bool m_open = false;
    bool m_paid = false;
    int m_price;
    bool m_Animated = false;
    double m_previousTime;
    float m_doneMove = 0.0f;
    float m_doneMove_real = 0.0f;
    float m_currentAltitude = 0.5f;
    int m_moveDirection = 0;
};

#endif // PROJET_DM_QUENTIN_LEBON_DOOR_HPP
