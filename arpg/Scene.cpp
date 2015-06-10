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
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->draw();
    }
}

void Scene::update()
{
    
}