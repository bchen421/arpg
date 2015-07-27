//
//  State.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/2/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "Player.h"
#include "State.h"

#pragma mark - Player Getters
JoystickInput State::getPlayerJoystickInput()
{
    return m_player->getJoystickInput();
}

SDL_RendererFlip State::getPlayerFlip()
{
    return m_player->m_flip;
}

SDL_Rect State::getPlayerBoundingBox()
{
    return m_player->m_boundingBox;
}

const std::vector<SDL_Rect>* State::getPlayerHitboxes()
{
    return &m_player->m_hitboxes;
}

const std::vector<SDL_Rect>* State::getPlayerHurtboxes()
{
    return &m_player->m_hurtboxes;
}

#pragma mark - Player Setters
void State::updatePlayerBoundingBox()
{
    m_player->updateBoundingBox();
}

void State::setPlayerSpriteID(std::string spriteID)
{
    m_player->setCurrentSpriteID(spriteID);
}

void State::setPlayerFlip(SDL_RendererFlip flip)
{
    m_player->m_flip = flip;
}

void State::setPlayerPosition(Vector2D position)
{
    m_player->m_position = position;
}

void State::setPlayerState(GameObjectState newState)
{
    m_player->changeState(newState);
}

/* Player Hitbox and Hurtbox Management */
void State::clearPlayerHitboxes()
{
    m_player->clearHitboxes();
}

void State::clearPlayerHurtboxes()
{
    m_player->clearHurtboxes();
}
void State::addPlayerHitbox(SDL_Rect hitbox)
{
    m_player->addHitbox(hitbox);
}

void State::addPlayerHurtbox(SDL_Rect hurtbox)
{
    m_player->addHurtbox(hurtbox);
}
