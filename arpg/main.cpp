//
//  main.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/5/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "GameManager.h"

// Temp includes until scenes and levels are built
#include "Sprite.h"

const std::string WINDOW_TITLE = "arpg";
const int WINDOW_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_YPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[])
{
    // Initialize the Game
    if (!GameManager::Instance()->init(WINDOW_TITLE.c_str(), WINDOW_XPOS, WINDOW_YPOS, WINDOW_WIDTH, WINDOW_HEIGHT, false))
    {
        printf("Failed to initialize Game Manager!\n");
        return 1;
    }
    
    // Temp init code until scenes are built
    Sprite strider;
    strider.init();
    
    while (GameManager::Instance()->getRunning())
    {
        GameManager::Instance()->handleEvents();
        GameManager::Instance()->update();
        
        // Temp loop code until scenes are built
        strider.update();
        
        GameManager::Instance()->clear();
        
        // Temp loop code until scenes are built
        strider.draw();
        
        GameManager::Instance()->render();
    }
    
    GameManager::Instance()->cleanup();
    
    return 0;
}
