//
// Created by lebonq on 23/12/22.
//

#include "Monster.hpp"


Monster::Monster(Model* model, glm::mat4 mat,WorldObject* shadow, int map_x, int map_y,int type,int life, int defense, int attack):
    InteractiveObject(model,shadow,mat, map_x, map_y), CombatEntity(life,defense,attack), m_type(type), m_real_x(map_x), m_real_z(map_y)
{
}

Monster::~Monster()
{
}

std::ostream& operator<<(std::ostream& os, const Monster& monster)
{
   os << "m_life: " << monster.getLife() << " m_defense: " << monster.getDefense() << " m_attack: " << monster.getAttack();
    return os;
}
void Monster::update(Player* player)
{
    player->getMapX();
    player->getMapY();
}

void Monster::getClicked(Player* player)
{
    if(this->m_type == DM_PROJECT_MONSTER_SKELETON){
        DEBUG_PRINT("You just hit a skeleton " << this->getAttack() << std::endl);
    }
    player->getRealZ();
}
void Monster::draw()
{
    InteractiveObject::draw();
}

void Monster::moveOnX(int direction){
     glm::mat4 mmatrix(1.0f);
     mmatrix = glm::translate(mmatrix, glm::vec3(this->getMapX()+direction + 1, 0.52, this->getMapY()));
     glm::mat4 smatrix(1.0f); //matric de l'ombre
      smatrix = glm::translate(smatrix, glm::vec3(this->getMapX()+direction+1, 0.01f, this->getMapY()));
      this->updateModelMatrix(mmatrix);
      this->m_shadow->updateModelMatrix(smatrix);
      this->m_PosMapX = this->getMapX()+direction ;
      this->m_shadow->setMapX(this->getMapX());
     this->m_real_x = this->getMapX();
}

void Monster::moveOnY(int direction){
     glm::mat4 mmatrix(1.0f); //matrice du monstre
     mmatrix = glm::translate(mmatrix, glm::vec3(this->getMapX()+1, 0.52, this->getMapY()+direction));
     glm::mat4 smatrix(1.0f); //matric de l'ombre
     smatrix = glm::translate(smatrix, glm::vec3(this->getMapX()+1, 0.01f, this->getMapY()+direction));
     this->updateModelMatrix(mmatrix);
     this->m_shadow->updateModelMatrix(smatrix);
     this->m_PosMapY = this->getMapY()+direction ;
     this->m_shadow->setMapY(this->getMapY());
     this->m_real_z = this->getMapY();
}

void Monster::draw(Player *player)
{
    float x = player->getRealX();
    float z = player->getRealZ();
    glUniform3fv(this->m_Model->getShaderProgram()->getPlayerPos(),1,glm::value_ptr(glm::vec3(x,0,z)));
    this->draw();
}
int Monster::getPreviousCell() const
{
    return m_previousCell;
}
void Monster::setPreviousCell(int previousCell)
{
    this->m_previousCell = previousCell;
}
