//
//  PlayerInputHandler.h
//  arpg
//
//  Created by Benjamin Chen on 7/24/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__PlayerInputHandler__
#define __arpg__PlayerInputHandler__

#include <map>

#include "Constants.h"
#include "InputHandler.h"

class PlayerInputHandler : public InputHandler
{
    
public:
    
    /* Game Loop Methods */
    virtual void handleInput(SDL_Event* event);
    
    /* Public Lifecycle Management Methods */
    virtual void init();
    virtual void clean();
    
    // Polymorphic Destructor
    virtual ~PlayerInputHandler() {}
    
private:
    
    // Private Utility Methods
    void handleMovementInput(SDL_Event* event);
    
    // Input Member Variables
    bool m_upInput;
    bool m_downInput;
    bool m_leftInput;
    bool m_rightInput;
    
    // Map of Key States to Input Commands
    std::map<JoystickInput,Uint8> m_joystickInputMap;
    
};


#endif /* defined(__arpg__PlayerInputHandler__) */
