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
    m_scenes.push(scene);
}

void SceneManager::popScene()
{
    if (!m_scenes.empty())
    {
        m_scenes.pop();
    }
}

Scene* SceneManager::getCurrentScene()
{
    if (m_scenes.empty())
    {
        return NULL;
    }
    else
    {
        return m_scenes.top();
    }
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

SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    
}
