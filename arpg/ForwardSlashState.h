//
//  ForwardSlash.h
//  arpg
//
//  Created by Benjamin Chen on 7/4/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__ForwardSlash__
#define __arpg__ForwardSlash__

#include "State.h"

class ForwardSlashState : public State
{
    
public:
    
    /* Polymorphic Destructor */
    virtual ~ForwardSlashState() { m_player = NULL; }
    
    virtual void init(Player* player);
    virtual void onEnter();
    virtual void handleInput(SDL_Event* event);
    virtual void update();
    virtual void onExit();
    
private:
    
    /* Temp method to load animation frames in */
    virtual void registerAnimations();
    
    /* Helper Methods */
    virtual void updateAnimationFrame();
    
    /* Private Data Member to track animation completion */
    bool m_completed;
    
};

#endif /* defined(__arpg__ForwardSlash__) */
