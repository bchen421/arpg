//
//  Player.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/13/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "TextureManager.h"
#include "Player.h"

void Player::updateBoundingBox()
{
    Sprite::updateBoundingBox();
    updateHitboxes();
    updateHurtboxes();
}

void Player::updateHurtboxes()
{
    clearHurtboxes();
    
    for (int i = 0; i < TextureManager::Instance()->getSpriteHurtboxes(m_spritesheet, m_currentSpriteID).size(); i++)
    {
        SDL_Rect box = TextureManager::Instance()->getSpriteHurtboxes(m_spritesheet, m_currentSpriteID)[i];
        if (m_flip == SDL_FLIP_NONE)
        {
            box.x = m_boundingBox.x + box.x;
            box.y = m_boundingBox.y + box.y;
        }
        else if (m_flip == SDL_FLIP_HORIZONTAL)
        {
            box.x = m_boundingBox.x + m_boundingBox.w - box.x - box.w;
            box.y = m_boundingBox.y + box.y;
        }
        addHurtbox(box);
    }
}

void Player::updateHitboxes()
{
    clearHitboxes();
    
    for (int i = 0; i < TextureManager::Instance()->getSpriteHitboxes(m_spritesheet, m_currentSpriteID).size(); i++)
    {
        SDL_Rect box = TextureManager::Instance()->getSpriteHitboxes(m_spritesheet, m_currentSpriteID)[i];
        
        if (m_flip == SDL_FLIP_NONE)
        {
            box.x = m_boundingBox.x + box.x;
            box.y = m_boundingBox.y + box.y;
        }
        else if (m_flip == SDL_FLIP_HORIZONTAL)
        {
            box.x = m_boundingBox.x + m_boundingBox.w - box.x - box.w;
            box.y = m_boundingBox.y + box.y;
        }
        addHitbox(box);
    }
}