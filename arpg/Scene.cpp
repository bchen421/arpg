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

#pragma mark - GameObjects Sorting
void Scene::qSortGameObjects(int startIndex, int endIndex)
{
    /* Base Case, already sorted */
    if ((endIndex - startIndex) < 1)
    {
        return;
    }
    
    /* 
     * Grab pivot and swap it with object at endIndex 
     * This keeps it out of the way for in place sorting
     */
    int pivotIndex = (endIndex - startIndex) / 2;
    swapGameObjectsAtIndex(pivotIndex, endIndex);
    
    /*
     * Sets ending pivotIndex to start at startIndex.
     * Iterate through the gameObjects vector from startIndex to
     * (endIndex - 1).  If object at index i is less than pivotObject value,
     * swap the value at i with the current ending pivotIndex value, and ++
     * to the ending pivotIndex.  Then two recursive calls are made
     * sort(startIndex, pivotIndex - 1) and sort (pivotIndex + 1, endIndex)
     */
    
    /* Set pivotIndex to start at startIndex */
    pivotIndex = startIndex;
    
    /*
     * Iterate through remaining objects, if less than, swap with current index
     * and then increment pivotIndex to the next index value
     */
    for (int i = startIndex; i < endIndex; i++)
    {
        if ((m_gameObjects[i]->getBoundingBox().y + m_gameObjects[i]->getBoundingBox().h) < (m_gameObjects[endIndex]->getBoundingBox().y + m_gameObjects[endIndex]->getBoundingBox().h))
        {
            swapGameObjectsAtIndex(i, pivotIndex);
            pivotIndex++;
        }
    }
    
    /* Moves pivot object to final destination */
    swapGameObjectsAtIndex(pivotIndex, endIndex);
    
    // To do: Implement insertion sort if less than n number of objects
    
    /* Recursive call to objects lower than pivotIndex */
    qSortGameObjects(startIndex, (pivotIndex - 1));
    /* Recursive call to objects higher than pivotIndex */
    qSortGameObjects(pivotIndex + 1, endIndex);
}

void Scene::swapGameObjectsAtIndex(int indexA, int indexB)
{
    GameObject* objectA = m_gameObjects[indexA];
    
    m_gameObjects[indexA] = m_gameObjects[indexB];
    m_gameObjects[indexB] = objectA;
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