//
//  SandboxScene.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "Strider.h"
#include "SkeletonWarrior.h"
#include "SandboxBackground.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "SandboxScene.h"

#pragma mark - Update Loop Methods
void SandboxScene::draw()
{
    if (!m_shouldExit)
    {
        int size = int(m_gameObjects.size());
        qSortGameObjects(0, (size - 1));
        Scene::draw();
    }
}

void SandboxScene::update(Uint32* deltaTime)
{
    if (!m_shouldExit)
    {
        Scene::update(deltaTime);
    }
}

void SandboxScene::handleInput(SDL_Event* event)
{
    if (!m_shouldExit)
    {
        if (event->type == SDL_KEYDOWN)
        {
            switch (event->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    reloadScene();
                    break;
                    
                default:
                    break;
            }
        }
        
        for (int i = 0; i < m_gameObjects.size(); i++)
        {
            if (!m_shouldExit)
            {
                if (m_gameObjects[i]->getGameObjectType() == kPlayerObject)
                {
                    dynamic_cast<Player*>(m_gameObjects[i])->handleInput(event);
                }
            }
        }
    }
}

#pragma mark - Scene Specific Methods
void SandboxScene::reloadScene()
{
    m_shouldExit = true;
    SandboxScene* scene = new SandboxScene();
    
    GameManager::Instance()->sceneTransition(scene);
}

#pragma mark - Initialization and Cleanup
void SandboxScene::load()
{
    TextureManager::Instance()->loadTexturePackerSpriteSheet("strider", "assets/spritesheets/strider.png", "assets/spritesheets/strider.json");
    
    TextureManager::Instance()->loadSpriteSheetMetaData("strider", "assets/metadata/strider.json");
    
    SkeletonWarrior* skwar01 = new SkeletonWarrior();
    skwar01->init();
    skwar01->setPosition({500,100});
    m_gameObjects.push_back(skwar01);
        
    Strider* player = new Strider();
    player->init();
    player->setPosition({100,100});
    m_gameObjects.push_back(player);
    m_playerObjects.push_back(player);
    
    SandboxBackground* background = new SandboxBackground();
    background->init();
    
    m_backgroundLayers.push_back(background);
}

void SandboxScene::clean()
{
    Scene::clean();
}

void SandboxScene::init()
{
    m_sceneID = kSandboxScene;
    
    load();
}