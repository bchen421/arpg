//
//  Strider.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/17/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "TextureManager.h"
#include "Strider.h"

#pragma mark - Update Loop Methods
void Strider::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox);
}

void Strider::update()
{
    handleState();
    updateAnimationFrame();
    updateBoundingBox();
}

void Strider::handleInput(SDL_Event *event)
{
    m_velocity = {0,0};
    bool walking = false;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() - 1);
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        walking = true;
        m_velocity.setX(m_velocity.getX() - 1);
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() + 1);
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        walking = true;
        m_velocity.setX(m_velocity.getX() + 1);
    }
    
    if (walking)
    {
        changeState(kStateWalking);
    }
    else
    {
        changeState(kStateIdle);
    }
}

#pragma mark - State Management Methods
void Strider::changeState(GameObjectState newState)
{
    switch (newState)
    {
        case kStateIdle:
            if (m_currentState != newState)
            {
                printf("Changing to idle state!\n");
                m_currentState = newState;
            }
            break;
            
        case kStateWalking:
            if (m_currentState != newState)
            {
                printf("Changing to walking state!\n");
                m_currentState = newState;
            }
            break;
            
        default:
            break;
    }
}

void Strider::handleState()
{
    switch (m_currentState)
    {
        case kStateIdle:
            idleState();
            break;
            
        case kStateWalking:
            walkingState();
            break;
            
        default:
            break;
    }
}

void Strider::walkingState()
{
    /* Normalize velocity */
    m_velocity.normalize();
    
    /* Calculate walking speed per frame */
    m_velocity *= m_walkingSpeed;
    
    /* Apply to position */
    m_position += m_velocity;
    
    if (m_currentAnimation == "strider_walking_animation")
    {
        m_currentAnimationFrame += 1;
    }
    else
    {
        m_currentAnimation = "strider_walking_animation";
        m_currentAnimationFrame = 0;
    }
}

void Strider::idleState()
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

# pragma Animation Helper Methods
void Strider::updateAnimationFrame()
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

/* Temporary method until data bound constructor can be build */
void Strider::registerAnimations()
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

#pragma mark - Lifecycle Methods
void Strider::clean()
{
    /* Stub Method */
}

void Strider::init()
{
    m_boundingBox = {0,0,1,1};
    m_gameObjectType = kPlayerObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {100,100};
    m_walkingSpeed = 1.0;
    
    registerAnimations();
    changeState(kStateIdle);
}