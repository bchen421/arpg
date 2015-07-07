//
//  Strider.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/17/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "GameManager.h"
#include "TextureManager.h"
#include "Strider.h"

#pragma mark - Update Loop Methods
void Strider::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox, m_flip);
    
    // void renderFromSpriteSheet(std::string spriteSheetID, std::string spriteID, SDL_Rect* destRect, SDL_RendererFlip flip = SDL_FLIP_NONE, const double angle = 0.0, SDL_Point* center = NULL);
    
    /* Debug drawing of bounding box */
    debug_render_color(0, 255, 0, 100);
    debug_sdl_rect(m_boundingBox);
    
    /* Debug Drawing of Hit Boxes */
    debug_render_color(0, 0, 255, 100);
    debug_sdl_rect(m_attackBoundingBox);
}

void Strider::update()
{
    if (m_playerState)
    {
        m_playerState->update();
    }
    else
    {
        handleState();
        updateAnimationFrame();
        updateBoundingBox();
    }
}

void Strider::handleInput(SDL_Event *event)
{
    if (m_playerState)
    {
        m_playerState->handleInput(event);
        return;
    }
    if (m_currentState == kStateForwardSlashAttack)
    {
        return;
    }
    
    m_velocity = {0,0};
    bool walking = false;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if (currentKeyStates[SDL_SCANCODE_U])
    {
        changeState(kStateForwardSlashAttack);
        return;
    }
    
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() - 1);
    }
    else if (currentKeyStates[SDL_SCANCODE_S])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() + 1);
    }
    
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        if (m_flip != SDL_FLIP_NONE)
        {
     
            m_flip = SDL_FLIP_NONE;
            m_position.setX(m_position.getX() - m_boundingBox.w);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() + 1);
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        if (m_flip != SDL_FLIP_HORIZONTAL)
        {
            m_flip = SDL_FLIP_HORIZONTAL;
            m_position.setX(m_position.getX() + m_boundingBox.w);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() - 1);
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
    if (m_playerState)
    {
        m_playerState->onExit();
        delete m_playerState;
        m_playerState = NULL;
    }

    switch (newState)
    {
        case kStateIdle:
            debug_print("%s\n", "Changing to State: kStateIdle");
            m_playerState = new IdleState();
            break;
            
        case kStateWalking:
            debug_print("%s\n", "Changing to State: kStateWalking");
            m_playerState = new WalkingState();
            break;
            
        case kStateForwardSlashAttack:
            debug_print("%s\n", "Changing to State: kStateForwardSlashAttack");
            m_playerState = new ForwardSlashState();
            break;
            
        default:
            break;
    }
    
    if (m_playerState)
    {
        m_playerState->init(this);
        m_playerState->onEnter();
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
            
        case kStateForwardSlashAttack:
            fslashState();
            break;
            
        default:
            break;
    }
}

void Strider::walkingState()
{
    m_currentAnimationFrame += 1;
    
    /* Normalize velocity */
    m_velocity.normalize();
    
    /* Calculate walking speed per frame */
    m_velocity *= m_walkingSpeed;
    
    /* Apply to position */
    m_position += m_velocity;
}

void Strider::idleState()
{
    m_currentAnimationFrame += 1;
}

void Strider::fslashState()
{
    m_currentAnimationFrame += 1;
    //updateBoundingBox();
    
    int x, y, w, h;
    
    if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        w = m_boundingBox.w - 25;
        x = m_boundingBox.x + m_boundingBox.w - w - 25;
        y = m_boundingBox.y;
        h = m_boundingBox.h / 2;
    }
    else
    {
        x = m_boundingBox.x + 25;
        y = m_boundingBox.y;
        w = m_boundingBox.w - 25;
        h = m_boundingBox.h / 2;
    }
    
    m_attackBoundingBox = {x,y,w,h};
    
    /* Completed Slashing Animation */
    if (m_currentAnimationFrame == m_animations["strider_fslash_animation"].size())
    {
        changeState(kStateIdle);
        m_attackBoundingBox = {0,0,0,0};
    }
}

#pragma mark - Getters
float Strider::getWalkingSpeed()
{
    return m_walkingSpeed;
}

# pragma mark - Animation Helper Methods
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

#pragma mark - Lifecycle Methods
void Strider::clean()
{
    /* Stub Method */
}

void Strider::init()
{
    m_boundingBox = {0,0,0,0};
    m_gameObjectType = kPlayerObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {0,0};
    m_walkingSpeed = 1.0;
    m_attackBoundingBox = {0,0,0,0};
    m_playerState = NULL;
    
    registerAnimations();
    changeState(kStateIdle);
}