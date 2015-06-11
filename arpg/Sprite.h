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

#include "GameObject.h"

class Sprite : public GameObject
{
    
public:
    
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
    std::string m_currentTextureID;
    
    // Member Methods for handling animations
    virtual void updateAnimationFrame();
    virtual void registerAnimations();
    
    // Class Members for Animation Handling
    std::map<std::string,std::vector<std::string>> m_animations;
    std::string m_currentAnimation;
    int m_currentAnimationFrame;
    
};

#endif /* defined(__arpg__Sprite__) */
