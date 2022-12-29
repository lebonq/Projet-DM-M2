//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_MONSTER_HPP
#define PROJET_DM_QUENTIN_LEBON_MONSTER_HPP

#include <ostream>
#include "InteractiveObject.hpp"
#include "Player.hpp"
class Monster : public InteractiveObject, public CombatEntity {
private:
    int m_type;

    float m_real_x = 0;
    float m_real_z = 0;

    int m_previousCell = -1;

public:
    int  getPreviousCell() const;
    void setPreviousCell(int previousCell);

public:
    Monster(Model* model, glm::mat4 mat,WorldObject* shadow, int map_x, int map_y,int type,int life, int defense, int attack);
    ~Monster();
    void  update(Player* player);
    bool  getClicked(Player* player, std::string& message, bool* printMessage) override;
    float getRealX() const
    {
        return m_real_x;
    };
    float getRealZ() const
    {
        return m_real_z;
    };
    void  setRealX(float x)
    {
        m_real_x = x;
    };
    void  setRealZ(float z)
    {
        m_real_z = z;
    }
    friend std::ostream& operator<<(std::ostream& os, const Monster& monster);

    void moveOnX(int direction);
    void moveOnY(int direction);
};

#endif // PROJET_DM_QUENTIN_LEBON_MONSTER_HPP
