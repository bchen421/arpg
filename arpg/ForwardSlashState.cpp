//
//  ForwardSlash.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/4/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "GameManager.h"
#include "Enemy.h"
#include "ForwardSlashState.h"

#pragma mark - Game Loop Methods
void ForwardSlashState::update()
{
    updateAnimationFrame();
    updatePlayerBoundingBox();
    if (m_completed)
    {
        setPlayerState(kStateIdle);
    }
    else
    {
        checkCollisions();
    }
}

void ForwardSlashState::handleInput(SDL_Event *event)
{
    // Nothing happens here during slashing!
}

#pragma mark - Helper Methods
void ForwardSlashState::checkCollisions()
{
    checkNonPlayerObjects();
}

bool ForwardSlashState::checkNonPlayerObjects()
{
    /* Grab a pointer to the current scene */
    Scene *currentScene = GameManager::Instance()->getCurrentScene();
    
    for (int i = 0; i < currentScene->getGameObjects().size(); i++)
    {
        if (dynamic_cast<Enemy*>(currentScene->getGameObjects()[i]))
        {
            //debug_print("I found an enemy at index %d\n", i);
            checkHitboxCollision(currentScene->getGameObjects()[i]);
        }
    }
    
    return false;
}

bool ForwardSlashState::checkHitboxCollision(GameObject* object)
{
    /* Check if I have hit them already */
    for (int i = 0; i < m_collidedGameObjects.size(); i++)
    {
        if (m_collidedGameObjects[i] == object)
        {
            return false;
        }
    }
    
    for (int i = 0; i < getPlayerHitboxes()->size(); i++)
    {
        SDL_Rect hitbox = getPlayerHitboxes()->operator[](i);
        SDL_Rect boundingBox = object->getBoundingBox();
        if (SDL_HasIntersection(&hitbox, &boundingBox))
        {
            debug_print("%s\n", "I hit someone!");
            m_collidedGameObjects.push_back(object);
        }
    }
    
    return false;
}

void ForwardSlashState::updateAnimationFrame()
{
    m_currentFrame++;
    
    if (m_currentFrame >= m_animations[m_currentAnimation].size())
    {
        //m_currentFrame = 0;
        //m_currentSpriteID = m_animations[m_currentAnimation][m_currentFrame];
        m_completed = true;
    }
    else
    {
        m_currentSpriteID = m_animations[m_currentAnimation][m_currentFrame];
    }
    
    setPlayerSpriteID(m_currentSpriteID);
}

void ForwardSlashState::registerAnimations()
{
    /* Vector of fslash animation frames */
    std::vector<std::string> fslashAnimationFrames;
    
    std::string fslash = "strider_fslash_";
    
    for (int i = 1; i < 12; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << fslash << 0 << i;
        }
        else
        {
            stream << fslash << i;
        }
        for (int j = 0; j < 3; j++)
        {
            fslashAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_fslash_animation"] = fslashAnimationFrames;
}

#pragma mark - Lifecycle Management
void ForwardSlashState::onExit()
{
    clearPlayerHitboxes();
    clearPlayerHurtboxes();
    m_player = NULL;
}

void ForwardSlashState::onEnter()
{
    m_currentFrame = -1;
    m_currentAnimation = "strider_fslash_animation";
    m_completed = false;
    m_collidedGameObjects.clear();
}

void ForwardSlashState::init(Player *player)
{
    m_player = player;
    m_velocity = {0,0};
    m_completed = false;
    m_collidedGameObjects.clear();
    registerAnimations();
}