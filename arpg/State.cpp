//
//  State.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/2/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "Player.h"
#include "State.h"

/* Player Setters */
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
