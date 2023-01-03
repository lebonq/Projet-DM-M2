//
// Created by lebonq on 23/12/22.
//

#ifndef PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP
#define PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP

#include "Model.hpp"
#include "Player.hpp"
#include "RenderedObject.hpp"
#include "WorldObject.hpp"

/**
 * This class is used by object which need to interact with the player
 */
class InteractiveObject : public RenderedObject {
protected:
    WorldObject* m_shadow; // allow us to store a shadow object if needed
public:
    InteractiveObject(Model* model, WorldObject* m_shadow, glm::mat4 mat, int map_x, int map_y);
    ~InteractiveObject() override                                                     = default;
    virtual bool getClicked(Player* player, std::string& message, bool* printMessage) = 0;
    virtual void draw();
    void         draw(Player* player);
    WorldObject* getMShadow() const;
    // Call update animation from main loop
    // One is to make the item face you other item move and fly
};

#endif // PROJET_DM_QUENTIN_LEBON_INTERACTIVEOBJECT_HPP
