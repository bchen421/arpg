//
//  PlayerInputHandler.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/24/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "GameUtilities.h"
#include "PlayerInputHandler.h"

#pragma mark - Game Loop Methods
void PlayerInputHandler::handleInput(SDL_Event* event)
{
    handleMovementInput(event);
}

#pragma mark - Utility Methods
void PlayerInputHandler::handleMovementInput(SDL_Event* event)
{
    m_upInput = false;
    m_downInput = false;
    m_leftInput = false;
    m_rightInput = false;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    /* Simultaneous Up and Down throws the down away */
    if (currentKeyStates[m_joystickInputMap[kUpPosition]])
    {
        m_upInput = true;
    }
    else if (currentKeyStates[m_joystickInputMap[kDownPosition]])
    {
        m_downInput = true;
    }
    
    /* Simultaneous Up and Down throws the down away */
    if (currentKeyStates[m_joystickInputMap[kLeftPosition]])
    {
        m_leftInput = true;
    }
    else if (currentKeyStates[m_joystickInputMap[kRightPosition]])
    {
        m_rightInput = true;
    }
    
    if (m_upInput)
    {
        if (m_leftInput)
        {
            m_joystickInput = kUpLeftPosition;
        }
        else if (m_rightInput)
        {
            m_joystickInput = kUpRightPosition;
        }
        else
        {
            m_joystickInput = kUpPosition;
        }
    }
    else if (m_downInput)
    {
        if (m_leftInput)
        {
            m_joystickInput = kDownLeftPosition;
        }
        else if (m_rightInput)
        {
            m_joystickInput = kDownRightPosition;
        }
        else
        {
            m_joystickInput = kDownPosition;
        }
    }
    else if (m_leftInput)
    {
        m_joystickInput = kLeftPosition;
    }
    else if (m_rightInput)
    {
        m_joystickInput = kRightPosition;
    }
    else
    {
        m_joystickInput = kNeutralPosition;
    }
}

#pragma mark - Lifecycle Management
void PlayerInputHandler::init()
{
    // Sets Movement Input Bools to false
    m_upInput = false;
    m_downInput = false;
    m_leftInput = false;
    m_rightInput = false;
    
    // Manages Joystick Inputs via Keyboard State
    m_joystickInputMap[kUpPosition] = SDL_SCANCODE_W;
    m_joystickInputMap[kDownPosition] = SDL_SCANCODE_S;
    m_joystickInputMap[kLeftPosition] = SDL_SCANCODE_A;
    m_joystickInputMap[kRightPosition] = SDL_SCANCODE_D;
}

void PlayerInputHandler::clean()
{
    m_joystickInputMap.clear();
}
