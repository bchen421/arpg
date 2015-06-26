//
//  Etest.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/18/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "TextureManager.h"
#include "Etest.h"

#pragma mark - Update Loop Methods
void Etest::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox, m_flip);
}

void Etest::update()
{
    handleState();
    updateAnimationFrame();
    updateBoundingBox();
}

#pragma mark - State Management Methods
void Etest::changeState(GameObjectState newState)
{
    switch (newState)
    {
        case kStateIdle:
            if (m_currentState != newState)
            {
                printf("Etest changing to idle state!\n");
                m_currentState = newState;
            }
            break;
            
        case kStateWalking:
            if (m_currentState != newState)
            {
                printf("Etest changing to walking state!\n");
                m_currentState = newState;
            }
            break;
            
        case kStateAggroed:
            if (m_currentState != newState)
            {
                printf("Etest changing to aggroed state!\n");
                m_currentState = newState;
            }
            break;
            
        case kStatePursuing:
            if (m_currentState != newState)
            {
                printf("Etest changing to pursuing state!\n");
                m_currentState = newState;
            }
            break;
            
            default:
            break;
    }
}

void Etest::handleState()
{
    switch (m_currentState)
    {
        case kStateIdle:
            idleState();
            break;
            
        default:
            break;
    }
}

void Etest::idleState()
{
    if (m_currentAnimation == "strider_idle_animation")
    {
        m_currentAnimationFrame += 1;
    }
    else
    {
        m_currentAnimation = "strider_idle_animation";
        m_currentAnimationFrame = 0;
    }
}

void Etest::walkingState()
{
    // Stub method
}

#pragma mark - Animation Helper Methods
void Etest::updateAnimationFrame()
{
    if (m_currentAnimationFrame >= m_animations[m_currentAnimation].size())
    {
        m_currentAnimationFrame = 0;
    }
    else
    {
        setCurrentSpriteID(m_animations[m_currentAnimation][m_currentAnimationFrame]);
    }
}

void Etest::registerAnimations()
{
    /* Vector of animation frame names */
    std::vector<std::string> idleAnimationFrames;
    
    /* Start of the idle animation keys */
    std::string idle = "strider_idle_";
    
    for (int i = 1; i < 20; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << idle << 0 << i;
        }
        else
        {
            stream << idle << i;
        }
        /* Number of frames each animation plays for */
        for (int j = 0; j < 6; j++)
        {
            idleAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_idle_animation"] = idleAnimationFrames;
    
    /* Vector of walking animation frames */
    std::vector<std::string> walkingAnimationFrames;
    
    std::string walking = "strider_walking_";
    
    for (int i = 1; i < 11; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << walking << 0 << i;
        }
        else
        {
            stream << walking << i;
        }
        for (int j = 0; j < 6; j++)
        {
            walkingAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_walking_animation"] = walkingAnimationFrames;
}

#pragma mark - Lifecycle Management
void Etest::clean()
{
    /* Stub method */
}

void Etest::init()
{
    m_boundingBox = {0,0,1,1};
    m_gameObjectType = kEnemyObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {400,100};
    m_movementSpeed = 1.0;
    m_flip = SDL_FLIP_HORIZONTAL;
    
    registerAnimations();
    changeState(kStateIdle);
}
