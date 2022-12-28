//
// Created by lebonq on 20/12/22.
//

#include "ModelsManager.hpp"
ModelsManager::ModelsManager()
{
    DEBUG_PRINT("Build ModelsManager " << std::endl);
    DEBUG_PRINT("Load Wall Model " << std::endl);
    Model* wall = new Model(DM_PROJECT_ID_MANAGER_WALL, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WALL), this->m_shaderManagerStatic);
    this->m_listModels.push_back(wall);
    DEBUG_PRINT("Load Floor Model " << std::endl);
    Model* floor = new Model(DM_PROJECT_ID_MANAGER_FLOOR, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_FLOOR), this->m_shaderManagerStatic);
    this->m_listModels.push_back(floor);
    DEBUG_PRINT("Load Water Model " << std::endl);
    Model* water = new Model(DM_PROJECT_ID_MANAGER_WATER, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WATER), this->m_shaderManagerStatic);
    this->m_listModels.push_back(water);
    DEBUG_PRINT("Load Gold Coin Model " << std::endl);
    Model* gold = new Model(DM_PROJECT_ID_MANAGER_GOLD_COIN, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_GOLD_COIN), this->m_shaderManagerFacing);
    this->m_listModels.push_back(gold);
    DEBUG_PRINT("Load Shadow Model " << std::endl);
    Model* shadow = new Model(DM_PROJECT_ID_MANAGER_SHADOW, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_SHADOW), this->m_shaderManagerStatic);
    this->m_listModels.push_back(shadow);
    DEBUG_PRINT("Load Skeleton Model " << std::endl);
    Model* skeleton = new Model(DM_PROJECT_ID_MANAGER_SKELETON, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_SKELETON), this->m_shaderManagerFacing);
    this->m_listModels.push_back(skeleton);
    DEBUG_PRINT("Load Door model " << std::endl);
    Model* door = new Model(DM_PROJECT_ID_MANAGER_DOOR, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_DOOR), this->m_shaderManagerStatic);
    this->m_listModels.push_back(door);
    DEBUG_PRINT("Load Floor Hole model " << std::endl);
    Model* hole = new Model(DM_PROJECT_ID_MANAGER_FLOOR_HOLE, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_FLOOR_HOLE), this->m_shaderManagerStatic);
    this->m_listModels.push_back(hole);
    DEBUG_PRINT("Load Ladder model " << std::endl);
    Model* ladder = new Model(DM_PROJECT_ID_MANAGER_LADDER, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_LADDER), this->m_shaderManagerFacing);
    this->m_listModels.push_back(ladder);
    DEBUG_PRINT("Load Gold Ingot model " << std::endl);
    Model* ingot = new Model(DM_PROJECT_ID_MANAGER_GOLD_INGOT, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_GOLD_INGOT), this->m_shaderManagerFacing);
    this->m_listModels.push_back(ingot);
    DEBUG_PRINT("Load Apple model " << std::endl);
    Model* apple = new Model(DM_PROJECT_ID_MANAGER_APPLE, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_APPLE), this->m_shaderManagerFacing);
    this->m_listModels.push_back(apple);
    DEBUG_PRINT("Load Beer model " << std::endl);
    Model* beer = new Model(DM_PROJECT_ID_MANAGER_BEER, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_BEER), this->m_shaderManagerFacing);
    this->m_listModels.push_back(beer);
    DEBUG_PRINT("Load Ham model " << std::endl);
    Model* ham = new Model(DM_PROJECT_ID_MANAGER_HAM, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_HAM), this->m_shaderManagerFacing);
    this->m_listModels.push_back(ham);
    DEBUG_PRINT("Load Meat model " << std::endl);
    Model* meat = new Model(DM_PROJECT_ID_MANAGER_MEAT, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_MEAT), this->m_shaderManagerFacing);
    this->m_listModels.push_back(meat);
    DEBUG_PRINT("Load Helmet model " << std::endl);
    Model* helmet = new Model(DM_PROJECT_ID_MANAGER_HELMET, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_HELMET), this->m_shaderManagerFacing);
    this->m_listModels.push_back(helmet);
    DEBUG_PRINT("Load Armor model " << std::endl);
    Model* armor = new Model(DM_PROJECT_ID_MANAGER_ARMOR, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_ARMOR), this->m_shaderManagerFacing);
    this->m_listModels.push_back(armor);
    DEBUG_PRINT("Load Gold Sword model " << std::endl);
    Model* sword = new Model(DM_PROJECT_ID_MANAGER_GOLD_SWORD, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_GOLD_SWORD), this->m_shaderManagerFacing);
    this->m_listModels.push_back(sword);
    DEBUG_PRINT("Load Wooden sword model " << std::endl);
    Model* woodSword = new Model(DM_PROJECT_ID_MANAGER_WOODEN_SWORD, this->m_texManager.getTexId(DM_PROJECT_ID_MANAGER_WOODEN_SWORD), this->m_shaderManagerFacing);
    this->m_listModels.push_back(woodSword);
}

ModelsManager::~ModelsManager()
{
    DEBUG_PRINT("Delete ModelsManager " << std::endl);
    for (auto model :this->m_listModels) {
        delete model;
    }
}
