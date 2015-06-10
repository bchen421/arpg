//
//  SceneManager.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "SceneManager.h"

SceneManager* SceneManager::s_pInstance = 0;

void SceneManager::pushScene(Scene* scene)
{
    scene->init();
    m_scenes.push(scene);
    m_currentScene = m_scenes.top();
}

void SceneManager::popScene()
{
    if (!m_scenes.empty())
    {
        m_scenes.pop();
    }
    
    m_currentScene = m_scenes.top();
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
