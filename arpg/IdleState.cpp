//
//  IdleState.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/1/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "Player.h"
#include "IdleState.h"

#pragma mark - Game Loop Methods
void IdleState::update()
{
    updateAnimationFrame();
    updatePlayerBoundingBox();
}

void IdleState::handleInput(SDL_Event* event)
{
    GameObjectState targetState = kStateNone;
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] ||
        currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D])
    {
        targetState = kStateWalking;
    }
    else if (currentKeyStates[SDL_SCANCODE_U])
    {
        targetState = kStateForwardSlashAttack;
    }
    
    if (targetState != kStateNone)
    {
        setPlayerState(targetState);
    }
}

#pragma mark - Helper Methods
void IdleState::updateAnimationFrame()
{
    m_currentFrame++;
    
    if (m_currentFrame >= m_animations[m_currentAnimation].size())
    {
        m_currentFrame = 0;
        m_currentSpriteID = m_animations[m_currentAnimation][m_currentFrame];
    }
    else
    {
        m_currentSpriteID = m_animations[m_currentAnimation][m_currentFrame];
    }
    
    setPlayerSpriteID(m_currentSpriteID);
}

void IdleState::registerAnimations()
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
}

#pragma mark - Lifecycle Management
void IdleState::onExit()
{
    m_player = NULL;
}

void IdleState::onEnter()
{
    m_currentFrame = -1;
    m_currentAnimation = "strider_idle_animation";
}

void IdleState::init(Player* player)
{
    m_player = player;
    registerAnimations();
}