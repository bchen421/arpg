//
//  GameManager.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/5/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "GameManager.h"

GameManager* GameManager::s_pInstance = 0;

#pragma mark - Game Loop and Setup
void GameManager::render()
{
    SDL_SetRenderDrawColor(s_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(s_pRenderer);
    SDL_RenderPresent(s_pRenderer);
}

void GameManager::update()
{

}

void GameManager::handleEvents()
{
    SDL_Event event;
    
    SDL_PollEvent(&event);
    
    if (event.type == SDL_QUIT)
    {
        quit();
    }
}

void GameManager::quit()
{
    m_running = false;
}

void GameManager::cleanup()
{
    SDL_DestroyRenderer(s_pRenderer);
    s_pRenderer = NULL;
    SDL_DestroyWindow(s_pWindow);
    s_pWindow = NULL;
    SDL_Quit();
}

bool GameManager::init(std::string title, int x, int y, int width, int height, bool fullscreen)
{
    if (!initSDL())
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    
    if (!createWindow(title, x, y, width, height, fullscreen))
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return false;
    }
    
    if (!createRenderer())
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

GameManager* GameManager::Instance()
{
    if (s_pInstance == 0)
    {
        s_pInstance = new GameManager();
        
        return s_pInstance;
    }
    
    return s_pInstance;
}

#pragma mark - Private Utility Methods
bool GameManager::createRenderer()
{
    Uint32 flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    s_pRenderer = SDL_CreateRenderer(s_pWindow, -1, flags);
    
    if (s_pRenderer == NULL)
    {
        return false;
    }

    return true;
}

bool GameManager::createWindow(std::string title, int x, int y, int width, int height, bool fullscreen)
{
    Uint32 flags;
    
    if (fullscreen)
    {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        flags = SDL_WINDOW_OPENGL;
    }
    
    s_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    
    if (!s_pWindow)
    {
        return false;
    }
    
    m_windowTitle = title;
    m_windowWidth = width;
    m_windowHeight = height;
    m_fullscreen = fullscreen;
    m_running = true;
    
    return true;
}

bool GameManager::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        
        return false;
    }
    else
    {
        return true;
    }
}


#pragma mark - Constructors and Destructors
GameManager::GameManager() : s_pWindow(NULL), s_pRenderer(NULL), m_windowWidth(0), m_windowHeight(0), m_fullscreen(false), m_running(false)
{
    // Stub Method
}

GameManager::~GameManager()
{

}
