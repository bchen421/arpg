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
#include "PlayerInputHandler.h"
#include "Strider.h"

#pragma mark - Update Loop Methods
void Strider::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox, m_flip);
    
    /* Debug drawing of bounding box */
    debug_render_color(255, 255, 0, 100);
    debug_sdl_rect(m_boundingBox);
    
    /* Debug Drawing of Hurt Boxes */
    debug_render_color(255, 0, 0, 100);
    for (int i = 0; i < m_hurtboxes.size(); i++)
    {
        debug_sdl_rect(m_hurtboxes[i]);
    }
    
    /* Debug Drawing of Hit Boxes */
    debug_render_color(0, 0, 255, 100);
    for (int i = 0; i < m_hitboxes.size(); i++)
    {
        debug_sdl_rect(m_hitboxes[i]);
    }    
}

void Strider::update()
{
    m_playerState->update();
}

void Strider::handleInput(SDL_Event *event)
{
    m_inputHandler->handleInput(event);
    m_playerState->handleInput(event);
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

#pragma mark - Getters
float Strider::getWalkingSpeed()
{
    return m_walkingSpeed;
}

#pragma mark - Lifecycle Methods
void Strider::clean()
{
    m_playerState = NULL;
    m_hitboxes.clear();
    m_hurtboxes.clear();
}

void Strider::init()
{
    m_boundingBox = {0,0,0,0};
    m_gameObjectType = kPlayerObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {0,0};
    m_walkingSpeed = 1.2;
    m_playerState = NULL;
    m_hitboxes.clear();
    m_hurtboxes.clear();
    m_inputHandler = new PlayerInputHandler();
    m_inputHandler->init();
    
    changeState(kStateIdle);
}
