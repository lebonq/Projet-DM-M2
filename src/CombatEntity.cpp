//
// Created by lebonq on 27/12/22.
//

#include "CombatEntity.hpp"
CombatEntity::CombatEntity(int life, int defense, int attack):m_life(life), m_defense(defense), m_attack(attack)
{
}

void CombatEntity::getAttacked(CombatEntity* attacker)
{
    int damage = attacker->getAttack() - this->getDefense();
    if (damage < 0)
    {
        damage = 0;
    }
    this->changeLife(-damage);
}
