//
//  GameObject.h
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef arpg_GameObject_h
#define arpg_GameObject_h

#include <SDL2/SDL.h>

#include "Constants.h"

class GameObject
{
    
public:
    
    // Getters and Setters
    SDL_Rect* getBoundingBox() { return &m_boundingBox; }
    
    
    // Update loop
    virtual void draw()=0;
    virtual void update()=0;
    
    // Initialization
    virtual bool init()=0;
    
    // Destructor Gets Called
    // Needs Polymorphism
    virtual ~GameObject(){}
    

protected:
    
    // SDL Data Members
    // Default Bounding Box
    // Will Eval to True for SDL_RectEmpty Call
    SDL_Rect m_boundingBox = {0,0,0,0};
};

#endif
