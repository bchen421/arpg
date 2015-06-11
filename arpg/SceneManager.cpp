//
//  SceneManager.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "SceneManager.h"

SceneManager* SceneManager::s_pInstance = 0;

#pragma mark - Scene Management Methods

bool SceneManager::runScene(Scene* scene)
{
    if (m_currentScene)
    {
        removeCurrentScene();
        m_scenes.pop();
    }
    scene->init();
    m_scenes.push(scene);
    m_currentScene = m_scenes.top();
    
    return true;
}

void SceneManager::removeCurrentScene()
{
    m_currentScene->shouldExit();
    m_currentScene->clean();
}

Scene* SceneManager::getCurrentScene()
{
    return m_currentScene;
}

#pragma mark - Constructor and Destructors
SceneManager* SceneManager::Instance()
{
    if (s_pInstance == 0)
    {
        s_pInstance = new SceneManager();
        return s_pInstance;
    }
    
    return s_pInstance;
}

SceneManager::SceneManager() : m_currentScene(nullptr)
{
    
}

SceneManager::~SceneManager()
{
    
}
