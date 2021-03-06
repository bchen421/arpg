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

void Sprite::updateBoundingBox()
{
    int anchorX = m_position.getX();
    int anchorY = m_position.getY();
    int width = TextureManager::Instance()->getSpriteWidth(m_spritesheet, m_currentSpriteID);
    int height = TextureManager::Instance()->getSpriteHeight(m_spritesheet, m_currentSpriteID);
    
    if (m_flip == SDL_FLIP_NONE)
    {
        m_boundingBox.x = anchorX;
        m_boundingBox.y = anchorY;
        m_boundingBox.w = width;
        m_boundingBox.h = height;
    }
    else if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        m_boundingBox.x = anchorX - width;
        m_boundingBox.y = anchorY;
        m_boundingBox.w = width;
        m_boundingBox.h = height;
    }
    
    updateHitboxes();
    updateHurtboxes();
}

void Sprite::updateHurtboxes()
{
    clearHurtboxes();
    
    for (int i = 0; i < TextureManager::Instance()->getSpriteHurtboxes(m_spritesheet, m_currentSpriteID).size(); i++)
    {
        SDL_Rect box = TextureManager::Instance()->getSpriteHurtboxes(m_spritesheet, m_currentSpriteID)[i];
        GameUtilities::transformChildRect(&m_boundingBox, &box, &m_flip);
        
        addHurtbox(box);
    }
}

void Sprite::updateHitboxes()
{
    clearHitboxes();
    
    for (int i = 0; i < TextureManager::Instance()->getSpriteHitboxes(m_spritesheet, m_currentSpriteID).size(); i++)
    {
        SDL_Rect box = TextureManager::Instance()->getSpriteHitboxes(m_spritesheet, m_currentSpriteID)[i];
        GameUtilities::transformChildRect(&m_boundingBox, &box, &m_flip);
        
        addHitbox(box);
    }
}

void Sprite::setCurrentSpriteID(std::string spriteID)
{
    m_currentSpriteID = spriteID;
}








