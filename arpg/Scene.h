//
//  Scene.h
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Scene__
#define __arpg__Scene__

#include <vector>

#include "Constants.h"
#include "Layer.h"
#include "GameObject.h"

class Scene
{
    
public:
    
    // Getters
    SceneID getSceneID() { return m_sceneID; }
    
    // Update Loop Methods
    virtual void draw();
    virtual void update();
    virtual void handleInput()=0;
    
    
private:
    
    // Unique Identifier for Scenes
    SceneID m_sceneID = kGenericScene;
    
    // Vector of background layers
    // Rendered First
    // To do: Sort by Z-Value
    std::vector<Layer*> m_backgroundLayers;
    
    // Vector of Sprites
    // Rendered after background layers
    // To do: Sort by Z-Value
    std::vector<GameObject*> m_objects;
    
    // Vector of UI Components
    // Rendered after sprites
    // To do: Sort by Z-Value
    std::vector<Layer*> m_UILayers;
    
};

#endif /* defined(__arpg__Scene__) */
