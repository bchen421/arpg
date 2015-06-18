//
//  Sprite.h
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Sprite__
#define __arpg__Sprite__

#include "GameObject.h"

class Sprite : public GameObject
{
    
public:
    
    /* Update loop */
    virtual void draw()=0;
    virtual void update()=0;
    
    /* Lifecycle */
    virtual void clean()=0;
    virtual void init()=0;
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState)=0;
    
    /* Public Getters */
    virtual Vector2D getPosition() { return m_position; }
    
    /* Polymorphic Destructor */
    virtual ~Sprite() {}
    
protected:
    
    /* Updates Bounding Box with (x,y) from m_position */
    virtual void updateBoundingBox();
    
    /* Abstraction to call other state handling methods */
    virtual void handleState()=0;
    
    /*
     * Wrapper to set the current spriteID and then
     * update width and height of m_boundingBox
     */
    virtual void setCurrentSpriteID(std::string spriteID);
    
    /* Spritesheet key to render spriteID from */
    std::string m_spritesheet;
    
    /*
     * Current spriteID use to query map of textures.
     * This should be set using setCurrentSpriteID() to ensure
     * that m_boundingBox has the current width and height
     */
    std::string m_currentSpriteID;
    
    /* Position of sprite.  Vector so it can do proper Vector math */
    Vector2D m_position;
    
};

#endif /* defined(__arpg__Sprite__) */
