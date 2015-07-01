//
//  Strider.h
//  arpg
//
//  Created by Benjamin Chen on 6/17/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Strider__
#define __arpg__Strider__

#include "Player.h"

class Strider : public Player
{
public:
    
    /* Update loop */
    virtual void draw();
    virtual void update();
    virtual void handleInput(SDL_Event *event);
    
    /* Lifecycle Management */
    virtual void clean();
    virtual void init();
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState);
    
    // Polymorphic Destructor
    virtual ~Strider(){}
    
protected:
    
    /* Abstraction to call other state handling methods */
    virtual void handleState();
    
    /* State Management Helpers */
    virtual void walkingState();
    virtual void idleState();
    virtual void fslashState();
    
    /* Updates animation frame from map */
    virtual void updateAnimationFrame();
    
    /* Temporary function until config data loader is worked on */
    virtual void registerAnimations();
    
    /* Bounding Boxes */
    SDL_Rect m_attackBoundingBox;
    
};

#endif /* defined(__arpg__Strider__) */
