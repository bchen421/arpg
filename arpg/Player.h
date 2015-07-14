//
//  Player.h
//  arpg
//
//  Created by Benjamin Chen on 6/16/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Player__
#define __arpg__Player__

#include <map>
#include <vector>

#include "PlayerStates.h"
#include "Sprite.h"

class Player : public Sprite
{
    friend class State;
        
public:
    
    /* Update loop */
    virtual void draw()=0;
    virtual void update()=0;
    virtual void handleInput(SDL_Event *event)=0;
    
    /* Lifecycle Management */
    virtual void clean()=0;
    virtual void init()=0;
    
    /* Getters */
    virtual float getWalkingSpeed()=0;
    
    /* Polymorphic Destructor */
    virtual ~Player(){}
    
protected:
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState)=0;
    
    /*
     * Player specific movement data members.  Velocity is normalized and then
     * multiplied by the appropriate speed data member to handle movement speed
     * and direction.
     */
    Vector2D m_velocity;
    float m_walkingSpeed;
    State* m_playerState;
    
    /*
     * Map with current animation name as key.  Value is a vector of spriteID
     * strings to query the TextureManager singleton for rendering
     */
    std::string m_currentAnimation;
    int m_currentAnimationFrame;
    std::map<std::string,std::vector<std::string>> m_animations;
    
};

#endif /* defined(__arpg__Player__) */
