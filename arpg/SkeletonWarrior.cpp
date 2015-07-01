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
    
    /* Debug Attack Range Rendering */
    debug_render_color(255, 0, 0, 100);
    debug_sdl_rect(m_attackRangeBoundingBox);
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
                m_currentAnimation = "skwar_idle_animation";
                m_currentAnimationFrame = 0;
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
                m_currentAnimation = "skwar_walking_animation";
                m_currentAnimationFrame = 0;
            }
            break;
            
        case kStateSlashAttack:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateSlashAttack");
                m_currentState = newState;
                m_currentAnimation = "skwar_slash_animation";
                m_currentAnimationFrame = -1;
            }
            
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
            
        case kStateAggroed:
            aggroState();
            break;
            
        case kStatePursuing:
            pursuingState();
            break;
            
        case kStateSlashAttack:
            slashAttackState();
            break;
            
        default:
            break;
    }
}

void SkeletonWarrior::idleState()
{
    m_currentAnimationFrame += 1;
    checkAggro();
}

void SkeletonWarrior::aggroState()
{
    /* Remove Aggro Box, no longer needed */
    m_aggroBoundingBox = {0, 0, 0, 0};
    
    // To do: Logic around selecting current target
    m_currentTarget = m_aggroList[0];
    
    // To do: Methods for attack, pursue, defend or pause
    // Set aggressiveness factor for random behaviour
    changeState(kStatePursuing);
}

void SkeletonWarrior::pursuingState()
{
    m_currentAnimationFrame += 1;
    if (!checkInAttackRange())
    {
        Vector2D targetPosition = getTargetPosition(m_currentTarget->getBoundingBox());
        
        m_velocity = targetPosition - m_position;
        m_velocity.normalize();
        m_velocity *= m_movementSpeed;
        m_position += m_velocity;
    }
    else
    {
        changeState(kStateSlashAttack);
    }
}

void SkeletonWarrior::slashAttackState()
{
    m_currentAnimationFrame += 1;
    
    /* Completed Slashing Animation */
    if (m_currentAnimationFrame == m_animations["skwar_slash_animation"].size())
    {
        changeState(kStatePursuing);
    }
}

bool SkeletonWarrior::checkAggro()
{
    /* Build Aggro Bounding Box */
    int x, y, w, h;
    if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        x = m_boundingBox.x - 100;
        y = m_boundingBox.y - 100;
        w = 100 + m_boundingBox.w;
        h = 200 + m_boundingBox.h;
    }
    else
    {
        x = m_boundingBox.x + m_boundingBox.w;
        y = m_boundingBox.y - 100;
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
            debug_print("%s\n", "Adding player to aggro list.");
            m_aggroList.push_back(currentScene->getPlayerObjects()[i]);
            changeState(kStateAggroed);
        }
    }
    
    return false;
}

bool SkeletonWarrior::checkInAttackRange()
{
    /* Build Attack Range Bounding Box */
    int x, y, w, h;
    w = 50;
    
    if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        x = m_boundingBox.x - w;
        y = m_boundingBox.y;
        h = m_boundingBox.h / 2;
    }
    else
    {
        x = m_boundingBox.x + m_boundingBox.w;
        y = m_boundingBox.y;
        h = m_boundingBox.h / 2;
    }
    
    m_attackRangeBoundingBox = {x,y,w,h};
    
    SDL_bool intersects;
    SDL_Rect playerRect = m_aggroList[0]->getBoundingBox();
    SDL_Rect resultRect;
    
    intersects = SDL_IntersectRect(&m_attackRangeBoundingBox, &playerRect, &resultRect);
    
    if (intersects == SDL_TRUE)
    {
        return true;
    }
    
    return false;
}

#pragma mark - Utility Methods
Vector2D SkeletonWarrior::getTargetPosition(SDL_Rect targetRect)
{
    Vector2D target;
    GameUtilities::CornersOfRect targetCorners;
    GameUtilities::CornersOfRect myCorners;
    
    targetCorners = GameUtilities::getCornersOfRect(&targetRect);
    myCorners = GameUtilities::getCornersOfRect(&m_boundingBox);
    
    if ((targetCorners.bottomLeft - myCorners.bottomRight).length() <
        (targetCorners.bottomRight - myCorners.bottomLeft).length())
    {
        /* Check if I need to be turned */
        if (m_flip == SDL_FLIP_HORIZONTAL)
        {
            m_position.setX(m_position.getX() - m_boundingBox.w);
        }
        /* Skeleton Warrior should face right */
        m_flip = SDL_FLIP_NONE;

        target = targetCorners.bottomLeft;
        
        /* I want my bottom right to match target's bottom left */
        target.setY(target.getY() - m_boundingBox.h);
        target.setX(target.getX() - m_boundingBox.w);
    }
    else
    {
        /* Check if I need to be turned */
        if (m_flip == SDL_FLIP_NONE)
        {
            m_position.setX(m_position.getX() + m_boundingBox.w);
        }
        
        /* Skeleton Warrior should face left */
         m_flip = SDL_FLIP_HORIZONTAL;
        
        target = targetCorners.bottomRight;
        
        /* I want my bottom left to target to match target's bottom right */
        target.setY(target.getY() - m_boundingBox.h);
    }
    
    //debug_print("X: %g Y: %g\n", target.getX(), target.getY());
    
    return target;
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
        for (int j = 0; j < 10; j++)
        {
            walkingAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["skwar_walking_animation"] = walkingAnimationFrames;
    
    std::vector<std::string> slashAnimationFrames;
    
    /* Slash Animation Name Prefix */
    std::string slash = "skwar_slash_";
    
    for (int i = 1; i < 6; i++)
    {
        std::stringstream stream;
        
        if (i < 10)
        {
            stream << slash << 0 << i;
        }
        else
        {
            stream << slash << i;
        }
        
        /* Add animation frames to Vector */
        for (int j = 0; j < 8; j++)
        {
            slashAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["skwar_slash_animation"] = slashAnimationFrames;
}

#pragma mark - Lifecycle Management
void SkeletonWarrior::clean()
{
    /* Stub Method */
}

void SkeletonWarrior::init()
{
    m_boundingBox = {0,0,0,0};
    m_aggroBoundingBox = {0,0,0,0};
    m_attackRangeBoundingBox = {0,0,0,0};
    m_gameObjectType = kEnemyObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {0,0};
    m_movementSpeed = 0.80;
    m_flip = SDL_FLIP_HORIZONTAL;
    
    registerAnimations();
    changeState(kStateIdle);
}