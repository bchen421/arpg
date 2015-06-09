//
//  Scene.h
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Scene__
#define __arpg__Scene__

#include "Constants.h"

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
    
    SceneID m_sceneID;
    
};

#endif /* defined(__arpg__Scene__) */
