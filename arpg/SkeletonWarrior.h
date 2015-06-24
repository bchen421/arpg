//
//  SkeletonWarrior.h
//  arpg
//
//  Created by Benjamin Chen on 6/22/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__SkeletonWarrior__
#define __arpg__SkeletonWarrior__

#include "Enemy.h"

class SkeletonWarrior : public Enemy
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
    virtual ~SkeletonWarrior(){};
    
protected:
    
    /* Abstraction Point for State Management */
    virtual void handleState();
    
    /* State Management Methods */
    virtual void idleState();
    virtual void walkingState();
    virtual bool checkAggro();
        
    /* Animation Frame Updates */
    virtual void updateAnimationFrame();
    
    /* Temp method until data bound constructor */
    virtual void registerAnimations();
    
};

#endif /* defined(__arpg__SkeletonWarrior__) */
