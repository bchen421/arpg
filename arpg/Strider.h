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
    
    /* Getters */
    virtual float getWalkingSpeed();
    
    // Polymorphic Destructor
    virtual ~Strider(){}
    
protected:
    
    /* Override to handle hit and hurtboxes */
    virtual void updateBoundingBox();
    void updateHurtboxes();
    void updateHitboxes();
    
    /* Bounding Boxes */
    SDL_Rect m_attackBoundingBox;
    
};

#endif /* defined(__arpg__Strider__) */
