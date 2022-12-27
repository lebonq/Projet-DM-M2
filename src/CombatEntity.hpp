//
// Created by lebonq on 27/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_COMBATENTITY_HPP
#define PROJET_DM_QUENTIN_LEBON_COMBATENTITY_HPP

#include <ostream>
class CombatEntity {
private:
    int m_life;
    int m_defense;
    int m_attack;

public:
    CombatEntity(int life, int defense, int attack);
    virtual ~CombatEntity() = default;
    void changeLife(int amount)
    {
        m_life += amount;
    };
    void changeDefense(int amount)
    {
        m_defense += amount;
    };
    void changeAttack(int amount)
    {
        m_attack += amount;
    };
    int getLife() const
    {
        return m_life;
    };
    int getDefense() const
    {
        return m_defense;
    };
    int getAttack() const
    {
        return m_attack;
    };
    void getAttacked(CombatEntity* attacker);

};

#endif // PROJET_DM_QUENTIN_LEBON_COMBATENTITY_HPP
