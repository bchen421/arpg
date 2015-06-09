//
//  main.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/5/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <iostream>

#include "Constants.h"
#include "GameManager.h"
#include "SceneManager.h"

int main(int argc, const char * argv[])
{
    // Initialize the Game
    if (!GameManager::Instance()->init(WINDOW_TITLE.c_str(), WINDOW_XPOS, WINDOW_YPOS, WINDOW_WIDTH, WINDOW_HEIGHT, false))
    {
        printf("Failed to initialize Game Manager!\n");
        return 1;
    }
    
    while (GameManager::Instance()->getRunning())
    {
        GameManager::Instance()->handleEvents();
        GameManager::Instance()->update();
        
        GameManager::Instance()->clear();
        GameManager::Instance()->render();
    }
    
    GameManager::Instance()->cleanup();
    
    return 0;
}
