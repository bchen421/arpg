//
//  Sprite.h
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Sprite__
#define __arpg__Sprite__

#include <map>
#include <vector>

#include "Vector2D.h"
#include "GameObject.h"

class Sprite : public GameObject
{
    
public:
    
    // Update loop
    virtual void draw();
    virtual void update();
    virtual void handleInput(SDL_Event* event);
    virtual void clean();
    
    // Getters and Setters
    virtual SDL_Point getPosition();
    virtual SDL_Rect getBoundingBox();
    virtual void changeState(PlayerState newState);
    
    // Initialization
    virtual bool init();
    
    // Constructor and Destructor
    Sprite();
    ~Sprite();
    
protected:
    
    // Getters and Setters
    virtual void setCurrentSpriteID(std::string spriteID);
    virtual void handleState();
    
    // SDL Data Members
    std::string m_currentSpriteID;
    std::string m_spritesheet;
    PlayerState m_currentState;
    Vector2D m_position;
    Vector2D m_velocity;
    
    // Member Methods for handling animations
    virtual void updateAnimationFrame();
    virtual void registerAnimations();
    
    // Class Members for Animation Handling
    std::map<std::string,std::vector<std::string>> m_animations;
    std::string m_currentAnimation;
    int m_currentAnimationFrame;
    
    // State Management Helpers
    void idleState();
    void walkingState();
    void updateBoundingBox();
    
};

#endif /* defined(__arpg__Sprite__) */
