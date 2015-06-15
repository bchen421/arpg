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
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox);
}

void Sprite::update()
{
    if (getPosition().x > GameManager::Instance()->getWindowWidth())
    {
        m_boundingBox.x = 0;
    }
    m_boundingBox.x += 1;
}

#pragma mark - Getters and Setters
SDL_Rect Sprite::getBoundingBox()
{
    return m_boundingBox;
}

SDL_Point Sprite::getPosition()
{
    return {m_boundingBox.x, m_boundingBox.y};
}

void Sprite::setPosition(SDL_Point pos)
{
    m_boundingBox.x = pos.x;
    m_boundingBox.y = pos.y;
}

void Sprite::setCurrentSpriteID(std::string spriteID)
{
    m_currentSpriteID = spriteID;
    
    m_boundingBox.w = TextureManager::Instance()->getSpriteWidth(m_spritesheet, m_currentSpriteID);
    m_boundingBox.h = TextureManager::Instance()->getSpriteHeight(m_spritesheet, m_currentSpriteID);
}

#pragma mark - Initialization and Cleanup
bool Sprite::init()
{
    // Should load and put the sprite in idle state
    m_spritesheet = "strider";
    
    setCurrentSpriteID("strider_idle_01.png");
    
    m_boundingBox.x = 100;
    m_boundingBox.y = 100;
    
    return true;
}

void Sprite::registerAnimations()
{
    std::vector<std::string> testAnimationFrames;
    std::string animationName = "testAnimation";
    m_animations[animationName] = testAnimationFrames;
    
    std::string idle = "strider_idle_00";
    std::string walk = "strider_walk_01";
    
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(idle);
    m_animations[animationName].push_back(walk);
    m_animations[animationName].push_back(walk);
}

void Sprite::updateAnimationFrame()
{
    
}

void Sprite::clean()
{
    
}

#pragma mark - Constructor and Destructors
Sprite::~Sprite()
{
    
}

Sprite::Sprite()
{
    m_gameObjectType = kSpriteObject;
    m_spritesheet = "";
    m_currentSpriteID = "";
    m_currentAnimation = "";
    m_currentAnimationFrame = 0;
    m_boundingBox = {0,0,1,1};
}