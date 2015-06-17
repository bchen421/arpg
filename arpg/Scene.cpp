//
//  Scene.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "Scene.h"

#pragma mark - Game Update Loop Methods
void Scene::draw()
{
    for (int i = 0; i < m_backgroundLayers.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_backgroundLayers[i]->draw();
        }
    }
    
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_gameObjects[i]->draw();
        }
    }
    
    for (int i = 0; i < m_UILayers.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_UILayers[i]->draw();
        }
    }
}

void Scene::update(Uint32* deltaTime)
{
    for (int i = 0; i < m_backgroundLayers.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_backgroundLayers[i]->update();
        }
    }
    
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_gameObjects[i]->update();
        }
    }
    
    for (int i = 0; i < m_UILayers.size(); i++)
    {
        if (!m_shouldExit)
        {
            m_UILayers[i]->update();
        }
    }
}

#pragma mark - Initialization
void Scene::clean()
{
    for (int i = 0; i < m_backgroundLayers.size(); i++)
    {
        m_backgroundLayers[i]->clean();
        delete m_backgroundLayers[i];
    }
    
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
        delete m_gameObjects[i];
    }
    
    for (int i = 0; i < m_UILayers.size(); i++)
    {
        m_UILayers[i]->clean();
        delete m_UILayers[i];
    }
    
    m_backgroundLayers.clear();
    m_gameObjects.clear();
    m_UILayers.clear();
}