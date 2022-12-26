//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP
#define PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP

#include "Model.hpp"
#include "Player.hpp"
#include "RenderedObject.hpp"
#include "WorldObject.hpp"

class InteractiveObject : public RenderedObject {
protected:
    WorldObject* m_shadow;
public:
    InteractiveObject(Model* model, WorldObject* m_shadow, glm::mat4 mat, int map_x, int map_y);
    virtual ~InteractiveObject() = default;
    virtual void update() = 0;
    virtual void getClicked(Player* player) = 0;
    virtual void draw() override;
    //Call update animation from main loop
    //One is to make the item face you other item move and fly
};

#endif // PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP
