//
//  SandboxScene.h
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__SandboxScene__
#define __arpg__SandboxScene__

#include "Scene.h"

class SandboxScene : public Scene
{
    
public:
    
    // Update loop methods
    virtual void draw();
    virtual void update();
    virtual void handleInput();
    
    // Initialization and Cleanup
    virtual void init();
    virtual void clean();
    
};

#endif /* defined(__arpg__SandboxScene__) */
