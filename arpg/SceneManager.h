//
//  SceneManager.h
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__SceneManager__
#define __arpg__SceneManager__

#include <stack>

#include "Scene.h"

class SceneManager
{
    
public:
    
    // Scene Management
    bool runScene(Scene* scene);
    
    // Getters
    Scene* getCurrentScene();
    
    // Singleton Instance
    static SceneManager* Instance();
    
private:
    
    // Private Scene Management Methods
    void removeCurrentScene();
    
    // Pointer to current scene
    Scene* m_currentScene;
    
    // Stack of Scenes
    std::stack<Scene*> m_scenes;
    
    // Singleton Pointer
    static SceneManager* s_pInstance;
    
    // Private Constructor and Destructor
    SceneManager();
    ~SceneManager();
    
};

#endif /* defined(__arpg__SceneManager__) */