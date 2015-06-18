//
//  Enemy.h
//  arpg
//
//  Created by Benjamin Chen on 6/17/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Enemy__
#define __arpg__Enemy__

#include <map>
#include <vector>

#include "Sprite.h"

class Enemy : public Sprite
{
    
public:
    
    /* Update Loop */
    virtual void draw()=0;
    virtual void update()=0;
    
    /* Lifecycle Management */
    virtual void clean()=0;
    virtual void init()=0;
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState)=0;
    
    /* Polymorphic Destructor */
    virtual ~Enemy(){}
    
protected:
    
    /* Abstraction point to handle state and invoke other methods */
    virtual void handleState()=0;
    
    /* State Management Methods */
    virtual void idleState()=0;
    virtual void walkingState()=0;
    
    /* Updates animation frame from animation map */
    virtual void updateAnimationFrame()=0;
    
    /* Temp method until data bound constructor is done */
    virtual void registerAnimations()=0;
    
    /* Enemy Specific Data Members */
    Vector2D m_velocity;
    float m_walkingSpeed;
    
    /* Current animation, frame and map container */
    std::string m_currentAnimation;
    int m_currentAnimationFrame;
    std::map<std::string,std::vector<std::string>> m_animations;
    
};

#endif /* defined(__arpg__Enemy__) */
