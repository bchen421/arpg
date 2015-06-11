//
//  SandboxScene.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "Sprite.h"
#include "SandboxBackground.h"
#include "SceneManager.h"
#include "SandboxScene.h"


#pragma mark - Update Loop Methods
void SandboxScene::draw()
{
    Scene::draw();
}

void SandboxScene::update()
{
    Scene::update();
}

void SandboxScene::handleInput(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN)
    {
        printf("A button was pressed!\n");
        switch (event->key.keysym.sym)
        {
            case SDLK_ESCAPE:
                reloadScene();
                break;
                
            default:
                break;
        }
    }
}

#pragma mark - Scene Specific Methods
void SandboxScene::reloadScene()
{
    SandboxScene* scene = new SandboxScene();
    
    SceneManager::Instance()->runScene(scene);
}

#pragma mark - Initialization and Cleanup
void SandboxScene::load()
{
    // Temporary method to use until loading via data is done
    // Temp loading of sprites and stuff
    Sprite* player = new Sprite();
    player->init();
    
    m_gameObjects.push_back(player);
    
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