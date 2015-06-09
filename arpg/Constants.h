//
//  Constants.h
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef arpg_Constants_h
#define arpg_Constants_h

#include <string>
#include <SDL2/SDL.h>

const std::string WINDOW_TITLE = "arpg";
const int WINDOW_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_YPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum SceneID
{
    kGenericScene,
    kSandboxScene,
};


#endif
