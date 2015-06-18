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

// Framerate Capping
const int SCREEN_FPS = 60;
const int TIME_PER_FRAME = 1000 / SCREEN_FPS;

// SDL Window Constants
const std::string WINDOW_TITLE = "Sandbox";
const int WINDOW_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_YPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum SceneID
{
    kGenericScene,
    kSandboxScene,
};

enum GameObjectType
{
    kGameObject,
    kSpriteObject,
    kPlayerObject,
    kEnemyObject,
};

enum GameObjectState
{
    /* Shared States */
    kStateIdle,
    
    /* Player States */
    kStateWalking,
    
    /* Enemy States */
    kStateAggroed,
    kStatePursuing,
};


#endif
