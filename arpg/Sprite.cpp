//
//  Sprite.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "GameManager.h"
#include "TextureManager.h"
#include "Sprite.h"

#pragma mark - Game Loop Methods
void Sprite::draw()
{
    TextureManager::Instance()->renderTexture(m_textureID, &m_boundingBox);
}

void Sprite::update()
{
    if (m_boundingBox.x > GameManager::Instance()->getWindowWidth())
    {
        m_boundingBox.x = 0;
    }
    m_boundingBox.x += 1;
}

void Sprite::clean()
{
    
}

#pragma mark - Initialization
bool Sprite::init()
{
    // Should load and put the sprite in idle state
    m_textureID = "strider_idle_00";
    
    TextureManager::Instance()->loadTexture("assets/images/strider.png", m_textureID);
    
    m_boundingBox.x = 100;
    m_boundingBox.y = 100;
    m_boundingBox.w = 170;
    m_boundingBox.h = 144;
    
    return true;
}

#pragma mark - Constructor and Destructors
Sprite::~Sprite()
{
    
}

Sprite::Sprite()
{
    m_gameObjectType = kSpriteObject;
    m_textureID = "";
}