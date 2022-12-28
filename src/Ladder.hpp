//
// Created by lebonq on 28/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_LADDER_HPP
#define PROJET_DM_QUENTIN_LEBON_LADDER_HPP

#include "InteractiveObject.hpp"
#include "Player.hpp"

class Ladder: public InteractiveObject {
public:
    Ladder(int type, Model* model, const glm::mat4& mat, int mapX, int mapY);

public:
    ~Ladder() override;
    void getClicked(Player* player) override;
    void draw() override;
};

#endif // PROJET_DM_QUENTIN_LEBON_LADDER_HPP
