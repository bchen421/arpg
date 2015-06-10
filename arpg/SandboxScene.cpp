//
//  SandboxScene.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "Sprite.h"
#include "SandboxScene.h"

#pragma mark - Update Loop Methods
void SandboxScene::draw()
{
    Scene::draw();
}

void SandboxScene::update()
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update();
    }
}

void SandboxScene::handleInput()
{
}

#pragma mark - Initialization and Cleanup
void SandboxScene::clean()
{
    // Stub method
    // Should loop through vectors and invoke clean and destroy
}

void SandboxScene::init()
{
    m_sceneID = kSandboxScene;
    
    // Temp loading of sprites and stuff
    Sprite* player = new Sprite();
    player->init();
    
    m_objects.push_back(player);
}