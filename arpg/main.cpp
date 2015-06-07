//
//  main.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/5/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "GameManager.h"

const std::string WINDOW_TITLE = "arpg";
const int WINDOW_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_YPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[])
{
    // Initialize the Game
    GameManager::Instance()->init(WINDOW_TITLE.c_str(), WINDOW_XPOS, WINDOW_YPOS, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    
    while (GameManager::Instance()->getRunning())
    {
        GameManager::Instance()->update();
    }
    
    return 0;
}
