//
// Created by lebonq on 28/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_LADDER_HPP
#define PROJET_DM_QUENTIN_LEBON_LADDER_HPP

#include "Player.hpp"
#include "WorldObject.hpp"
class Ladder: public WorldObject {
public:
    Ladder(int type, Model* model, const glm::mat4& mat, int mapX, int mapY);
    void draw() override;

public:
    ~Ladder() override;
    void draw(Player* player);
};

#endif // PROJET_DM_QUENTIN_LEBON_LADDER_HPP
