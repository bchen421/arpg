//
//  Etest.h
//  arpg
//
//  Created by Benjamin Chen on 6/18/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Etest__
#define __arpg__Etest__

#include "Enemy.h"

class Etest : public Enemy
{
    
public:
    
    /* Update Loop Methods */
    virtual void draw();
    virtual void update();
    
    /* Lifecycle Management Methods */
    virtual void clean();
    virtual void init();
    
    /* Public State Changing Interface */
    virtual void changeState(GameObjectState newState);
    
    /* Polymorphic Destructor */
    virtual ~Etest(){};
    
protected:
    
    /* Abstraction point for state management */
    virtual void handleState();
    
    /* State Management Methods */
    virtual void idleState();
    virtual void walkingState();
    
    /* Animation Frame Updates */
    virtual void updateAnimationFrame();
    
    /* Temp method until data bound constructor */
    virtual void registerAnimations();
    
};

#endif /* defined(__arpg__Etest__) */
