//
//  Sprite.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "GameManager.h"
#include "TextureManager.h"
#include "Sprite.h"

#pragma mark - Game Loop Methods
void Sprite::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox);
}

void Sprite::update()
{
    handleState();
    updateAnimationFrame();
    updateBoundingBox();
}

void Sprite::handleInput(SDL_Event* event)
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

#pragma mark - Player State Management Methods
void Sprite::walkingState()
{
    // Change to be based on speed
    m_velocity.normalize();
    m_velocity *= m_walkingSpeed;
    printf("X velocity: %g\n", m_velocity.getX());
    printf("Y velocity: %g\n", m_velocity.getY());
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

void Sprite::idleState()
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

void Sprite::updateBoundingBox()
{
    m_boundingBox.x = m_position.getX();
    m_boundingBox.y = m_position.getY();
}

#pragma mark - Getters and Setters
void Sprite::changeState(PlayerState newState)
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
                printf("Changing to moving state!\n");
                m_currentState = newState;
            }
            
        default:
            break;
    }
}

void Sprite::handleState()
{
    switch (m_currentState)
    {
        case kStateIdle:
            idleState();
            break;
            
        case kStateWalking:
            walkingState();
            
        default:
            break;
    }
}

SDL_Rect Sprite::getBoundingBox()
{
    return m_boundingBox;
}

SDL_Point Sprite::getPosition()
{
    return {m_boundingBox.x, m_boundingBox.y};
}

void Sprite::setCurrentSpriteID(std::string spriteID)
{
    m_currentSpriteID = spriteID;
    
    m_boundingBox.w = TextureManager::Instance()->getSpriteWidth(m_spritesheet, m_currentSpriteID);
    m_boundingBox.h = TextureManager::Instance()->getSpriteHeight(m_spritesheet, m_currentSpriteID);
}

#pragma mark - Initialization and Cleanup
bool Sprite::init()
{
    // Object specific attributes
    m_walkingSpeed = 1.0;
    
    // Should load and put the sprite in idle state
    m_spritesheet = "strider";
    
    // Setup Animation Frames
    registerAnimations();
    
    m_position = {100,100};
    m_currentState = kStateIdle;
    changeState(kStateIdle);
    
    return true;
}

void Sprite::registerAnimations()
{
    // Idle Animation Frames
    std::vector<std::string> idleAnimationFrames;
    
    std::string idle = "strider_idle_";
    
    for (int i = 1; i < 20; i++)
    {
        std::stringstream sstream;
        if (i < 10)
        {
            sstream << idle << 0 << i;
            for (int j = 0; j < 6; j++)
            {
                idleAnimationFrames.push_back(sstream.str());
            }
        }
        else
        {
            sstream << idle << i;
            for (int j = 0; j < 6; j++)
            {
                idleAnimationFrames.push_back(sstream.str());
            }
        }
    }
    
    m_animations["strider_idle_animation"] = idleAnimationFrames;
    
    // Walking Animation Frams
    std::vector<std::string> walkingAnimationFrames;
    
    std::string walking = "strider_walking_";
    
    for (int i = 1; i < 11; i++)
    {
        std::stringstream sstream;
        if (i < 10)
        {
            sstream << walking << 0 << i;
            for (int j = 0; j < 6; j++)
            {
                walkingAnimationFrames.push_back(sstream.str());
            }
        }
        else
        {
            sstream << walking << i;
            for (int j = 0; j < 6; j++)
            {
                walkingAnimationFrames.push_back(sstream.str());
            }
        }
    }
    
    m_animations["strider_walking_animation"] = walkingAnimationFrames;
}

void Sprite::updateAnimationFrame()
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

void Sprite::clean()
{
    
}

#pragma mark - Constructor and Destructors
Sprite::~Sprite()
{
    
}

Sprite::Sprite()
{
    m_gameObjectType = kSpriteObject;
    m_spritesheet = "";
    m_currentSpriteID = "";
    m_currentAnimation = "";
    m_currentAnimationFrame = 0;
    m_boundingBox = {0,0,1,1};
    m_currentState = kStateIdle;
    m_velocity = Vector2D(0,0);
    m_walkingSpeed = 0.0;
}