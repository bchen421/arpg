//
//  SkeletonWarrior.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/22/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "GameManager.h"
#include "TextureManager.h"
#include "SkeletonWarrior.h"

#pragma mark - Update Loop Methods
void SkeletonWarrior::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox, m_flip);
    
    /* Debug drawing of bounding box */
    debug_render_color(0, 255, 0, 100);
    debug_sdl_rect(m_boundingBox);
    
    /* Debug Aggro Rect Rendering */
    debug_render_color(255, 0, 0, 100);
    debug_sdl_rect(m_aggroBoundingBox);
}

void SkeletonWarrior::update()
{
    handleState();
    updateAnimationFrame();
    updateBoundingBox();
}

#pragma mark - State Management Methods
void SkeletonWarrior::changeState(GameObjectState newState)
{
    switch (newState)
    {
        case kStateIdle:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateIdle");
                m_currentState = newState;
            }
            break;
            
        case kStateWalking:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateWalking");
                m_currentState = newState;
            }
            break;
            
        case kStateAggroed:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateAggroed");
                m_currentState = newState;
            }
            break;
            
        case kStatePursuing:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStatePursuing");
                m_currentState = newState;
            }
            break;
            
        default:
            break;
    }
}

void SkeletonWarrior::handleState()
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

void SkeletonWarrior::idleState()
{
    checkAggro();
    if (m_currentAnimation == "skwar_idle_animation")
    {
        m_currentAnimationFrame += 1;
    }
    else
    {
        m_currentAnimation = "skwar_idle_animation";
        m_currentAnimationFrame = 0;
    }
}

bool SkeletonWarrior::checkAggro()
{
    /* Build Aggro Bounding Box */
    int x, y, w, h;
    if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        x = m_position.getX() - 100;
        y = m_position.getY() - 100;
        w = 100 + m_boundingBox.w;
        h = 200 + m_boundingBox.h;
    }
    else
    {
        x = m_position.getX() + m_boundingBox.w;
        y = m_position.getY() - 100;
        w = 100 + m_boundingBox.w;
        h = 200 + m_boundingBox.h;
    }
    m_aggroBoundingBox = {x,y,w,h};
    
    /* Variables to hold intersection test results */
    SDL_bool intersects;
    SDL_Rect playerRect;
    SDL_Rect resultRect;
    
    /* Grab Current Scene and player objects vector */
    Scene* currentScene = GameManager::Instance()->getCurrentScene();
    for (int i = 0; i < currentScene->getPlayerObjects().size(); i++)
    {
        playerRect = currentScene->getPlayerObjects()[i]->getBoundingBox();
        
        intersects = SDL_IntersectRect(&m_aggroBoundingBox, &playerRect, &resultRect);
        
        if (intersects == SDL_TRUE)
        {
            debug_print("%s\n", "Aggro on player");
        }
    }
    
    return false;
}

void SkeletonWarrior::walkingState()
{
    // Stub
}

#pragma mark - Animation Helper Methods
void SkeletonWarrior::updateAnimationFrame()
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

void SkeletonWarrior::registerAnimations()
{
    /* Vector of Idle Animation Frames */
    std::vector<std::string> idleAnimationFrames;
    
    /* Idle Animation Name Prefix */
    std::string idle = "skwar_idle_";
    
    for (int i = 1; i < 2; i++)
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
        
        /* Add animation frames to Vector */
        for (int j = 0; j < 6; j++)
        {
            idleAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["skwar_idle_animation"] = idleAnimationFrames;
    
    /* Vector of Walking Animation Frames */
    std::vector<std::string> walkingAnimationFrames;
    
    /* Walking Animation Name Prefix */
    std::string walking = "skwar_walking_";
    
    for (int i = 1; i < 9; i++)
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
        
        /* Add animation frames to Vector */
        for (int j = 0; j < 6; j++)
        {
            walkingAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["skwar_walking_animation"] = walkingAnimationFrames;
}

#pragma mark - Lifecycle Management
void SkeletonWarrior::clean()
{
    /* Stub Method */
}

void SkeletonWarrior::init()
{
    m_boundingBox = {0,0,1,1};
    m_gameObjectType = kEnemyObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {400,100};
    m_walkingSpeed = 1.0;
    m_flip = SDL_FLIP_HORIZONTAL;
    
    registerAnimations();
    changeState(kStateIdle);
}