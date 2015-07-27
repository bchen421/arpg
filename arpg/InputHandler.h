//
//  InputHandler.h
//  arpg
//
//  Created by Benjamin Chen on 7/24/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__InputHandler__
#define __arpg__InputHandler__

#include <SDL2/SDL.h>

// Abstract Class for Input Handling
class InputHandler
{
    
public:
    
    /* Game Loop Methods */
    virtual void handleInput(SDL_Event* event) = 0;
    
    /* Getters for Current Input State */
    JoystickInput getJoystickInput() { return m_joystickInput; }
    
    /* Lifecycle Management Methods */
    virtual void init() = 0;
    virtual void clean() = 0;
    
    /* Polymorphic Destructor */
    virtual ~InputHandler() {}
    
protected:
    
    /* Output Member Variables */
    JoystickInput m_joystickInput;
    
};


#endif /* defined(__arpg__InputHandler__) */
