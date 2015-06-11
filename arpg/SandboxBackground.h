//
//  SandboxBackground.h
//  arpg
//
//  Created by Benjamin Chen on 6/10/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__SandboxBackground__
#define __arpg__SandboxBackground__

#include <string>

#include "Layer.h"

class SandboxBackground : public Layer
{
    
public:
    
    // Update Loop
    virtual void draw();
    virtual void update();
    
    // Initialization
    virtual void clean();
    virtual void init();
    
};

#endif /* defined(__arpg__SandboxBackground__) */
