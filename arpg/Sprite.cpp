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
    m_boundingBox.x = m_position.getX();
    m_boundingBox.y = m_position.getY();
}

void Sprite::setCurrentSpriteID(std::string spriteID)
{
    m_currentSpriteID = spriteID;
    
    m_boundingBox.w = TextureManager::Instance()->getSpriteWidth(m_spritesheet, m_currentSpriteID);
    m_boundingBox.h = TextureManager::Instance()->getSpriteHeight(m_spritesheet, m_currentSpriteID);
}








