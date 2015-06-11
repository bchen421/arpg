//
//  SandboxBackground.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/10/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "TextureManager.h"
#include "SandboxBackground.h"

#pragma mark - Update Loop Methods

void SandboxBackground::draw()
{
    TextureManager::Instance()->renderTexture(m_textureID, NULL);
}

void SandboxBackground::update()
{
}

#pragma mark - Initialization and Cleanup

void SandboxBackground::clean()
{
    
}

void SandboxBackground::init()
{
    m_textureID = "sandboxBackground";
    TextureManager::Instance()->loadTexture("assets/images/background.bmp", m_textureID);
}