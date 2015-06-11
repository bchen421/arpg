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

    TextureManager::Instance()->renderTexture(m_currentTextureID, &m_boundingBox);
}

void Sprite::update()
{
    if (m_boundingBox.x > GameManager::Instance()->getWindowWidth())
    {
        m_boundingBox.x = 0;
    }
    m_boundingBox.x += 1;
    
    updateAnimationFrame();
}

#pragma mark - Initialization and Cleanup
bool Sprite::init()
{
    // Should load and put the sprite in idle state
    m_currentTextureID = "strider_idle_00";
    
    TextureManager::Instance()->loadTexture("assets/images/strider.png", "strider_idle_00");
    
    m_boundingBox.x = 100;
    m_boundingBox.y = 100;
    m_boundingBox.w = 170;
    m_boundingBox.h = 144;
    
    TextureManager::Instance()->loadTexture("assets/images/strider_walk_01.png", "strider_walk_01");
    
    registerAnimations();
    
    m_currentAnimation = "testAnimation";
    
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
    if (m_currentAnimationFrame < m_animations[m_currentAnimation].size())
    {
        m_currentTextureID = m_animations[m_currentAnimation][m_currentAnimationFrame];
    }
    else
    {
        m_currentAnimationFrame = 0;
        m_currentTextureID = m_animations[m_currentAnimation][m_currentAnimationFrame];
    }
    
    m_currentAnimationFrame++;
}

void Sprite::clean()
{
    // Todo: Clean up m_animations map;
}

#pragma mark - Constructor and Destructors
Sprite::~Sprite()
{
    
}

Sprite::Sprite()
{
    m_gameObjectType = kSpriteObject;
    m_currentTextureID = "";
    m_currentAnimation = "";
    m_currentAnimationFrame = 0;
}