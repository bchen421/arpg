//
//  Layer.h
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Layer__
#define __arpg__Layer__

class Layer
{
    
public:
    
    // Update Loop
    virtual void draw()=0;
    virtual void update()=0;
    
    // Initialization
    virtual void clean()=0;
    virtual void init()=0;
    
    // Destructor for polymorphism
    virtual ~Layer(){}
    
protected:
    
    std::string m_textureID = "";
    SDL_Rect m_boundingBox = {0,0,0,0};
    
};

#endif /* defined(__arpg__Layer__) */
