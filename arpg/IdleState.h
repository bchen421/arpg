//
//  IdleState.h
//  arpg
//
//  Created by Benjamin Chen on 7/1/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__IdleState__
#define __arpg__IdleState__

#include "State.h"

class IdleState : public State
{
    
public:
    
    /* Polymorphic Destructor */
    virtual ~IdleState() { m_player = NULL; }
    
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

#endif /* defined(__arpg__IdleState__) */
