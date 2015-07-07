//
//  WalkingState.h
//  arpg
//
//  Created by Benjamin Chen on 7/2/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__WalkingState__
#define __arpg__WalkingState__

#include "State.h"

class WalkingState : public State
{
    
public:
    
    /* Polymorphic Destructor */
    virtual ~WalkingState() { m_player = NULL; }
    
    virtual void init(Player* player);
    virtual void onEnter();
    virtual void handleInput(SDL_Event* event);
    virtual void update();
    virtual void onExit();
    
private:
    
    /* Temp Method to load animation frames in */
    virtual void registerAnimations();
    
    /* Helper Methods */
    virtual void updateAnimationFrame();
};

#endif /* defined(__arpg__WalkingState__) */
