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
    
    // Getters and Setters
    std::string getTextureID() { return m_textureID; }
    
    // Update loop
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    // Initialization
    virtual bool init();
    
    // Constructor and Destructor
    Sprite();
    ~Sprite();
    
protected:
    
    // SDL Data Members
    std::string m_textureID;
    
};

#endif /* defined(__arpg__Sprite__) */
