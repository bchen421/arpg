//
//  Sprite.h
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Sprite__
#define __arpg__Sprite__

#include <SDL2/SDL.h>

class Sprite
{
    
public:
    
    // Getters and Setters
    SDL_Rect* getBoundingBox();
    
    // Update loop
    void draw();
    void update();
    
    // Initialization
    bool init();
    
    // Constructor and Destructor
    Sprite();
    ~Sprite();
    
private:
    
    // SDL Data Members
    SDL_Rect m_boundingBox;
    std::string m_textureID;
    
};

#endif /* defined(__arpg__Sprite__) */
