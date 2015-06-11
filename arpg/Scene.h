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
#include <map>

#include "Constants.h"
#include "Layer.h"
#include "GameObject.h"

class Scene
{
    
public:
    
    // Scene Transition
    void shouldExit() { m_shouldExit = true; }
    bool exiting() { return m_shouldExit; }
    
    // Getters
    SceneID getSceneID() { return m_sceneID; }
    
    // Update Loop Methods
    virtual void draw();
    virtual void update();
    virtual void handleInput(SDL_Event* event)=0;
    
    // Initialization and Cleanup
    virtual void init()=0;
    virtual void clean();
    virtual ~Scene(){}
    
    
protected:
    
    // Member bool to help with scene transition
    bool m_shouldExit = false;
    
    // Unique Identifier for Scenes
    SceneID m_sceneID = kGenericScene;
    
    // Vector of background layers
    // Rendered First
    // To do: Sort by Z-Value
    std::vector<Layer*> m_backgroundLayers;
    
    // Vector of Sprites
    // Rendered after background layers
    // To do: Sort by Z-Value
    std::vector<GameObject*> m_gameObjects;
    
    // Vector of UI Components
    // Rendered after sprites
    // To do: Sort by Z-Value
    std::vector<Layer*> m_UILayers;
    
};

#endif /* defined(__arpg__Scene__) */
