//
//  WalkingState.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/2/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "WalkingState.h"

#include <sstream>

#include "Player.h"
#include "IdleState.h"

#pragma mark - Game Loop Methods
void WalkingState::update()
{
    updateAnimationFrame();
    updatePlayerBoundingBox();
    m_velocity.normalize();
    m_velocity *= m_player->getWalkingSpeed();
    
    setPlayerPosition(m_player->getPosition() + m_velocity);
}

void WalkingState::handleInput(SDL_Event* event)
{
    m_velocity = {0,0};
    bool walking = false;
    
    JoystickInput currentInput = getPlayerJoystickInput();
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if (currentKeyStates[SDL_SCANCODE_U])
    {
        setPlayerState(kStateForwardSlashAttack);
        return;
    }
    
    if (currentInput == kUpPosition || currentInput == kUpRightPosition
        || currentInput == kUpLeftPosition)
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() - 1);
    }
    else if (currentInput == kDownPosition || currentInput == kDownRightPosition
             || currentInput == kDownLeftPosition)
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() + 1);
    }
    
    if (currentInput == kRightPosition || currentInput == kDownRightPosition
        || currentInput == kUpRightPosition)
    {
        if (m_player->getFlip() != SDL_FLIP_NONE)
        {
            setPlayerFlip(SDL_FLIP_NONE);
            Vector2D player_position = m_player->getPosition();
            player_position.setX(player_position.getX() - m_player->getBoundingBox().w);
            setPlayerPosition(player_position);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() + 1);
    }
    else if (currentInput == kLeftPosition || currentInput == kUpLeftPosition ||
             currentInput == kDownLeftPosition)
    {
        if (m_player->getFlip() != SDL_FLIP_HORIZONTAL)
        {
            setPlayerFlip(SDL_FLIP_HORIZONTAL);
            Vector2D player_position = m_player->getPosition();
            player_position.setX(player_position.getX() + m_player->getBoundingBox().w);
            setPlayerPosition(player_position);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() - 1);
    }
    
    if (!walking)
    {
        setPlayerState(kStateIdle);
    }

}

#pragma mark - Helper Methods
void WalkingState::updateAnimationFrame()
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

void WalkingState::registerAnimations()
{
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
void WalkingState::onExit()
{
    m_player = NULL;
}

void WalkingState::onEnter()
{
    m_currentFrame = -1;
    m_currentAnimation = "strider_walking_animation";
}

void WalkingState::init(Player* player)
{
    m_player = player;
    m_velocity = {0,0};
    registerAnimations();
}
