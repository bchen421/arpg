//
//  TextureManager.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <SDL2_image/SDL_image.h>

#include "GameManager.h"
#include "TextureManager.h"


TextureManager* TextureManager::s_pInstance = 0;

#pragma mark - Utility Methods
void TextureManager::renderTexture(std::string textureID, SDL_Rect* destRect)
{
    if (m_textures.count(textureID) > 0)
    {
        SDL_RenderCopy(GameManager::Instance()->getRenderer(), m_textures[textureID], NULL, destRect);
    }
    else
    {
        printf("Texture ID: %s does not exist!", textureID.c_str());
    }
}

bool TextureManager::loadTexture(std::string filename, std::string textureID)
{
    if (m_textures.count(textureID))
    {
        return true;
    }
    
    SDL_Surface* tempSurface = IMG_Load(filename.c_str());
    
    if (!tempSurface)
    {
        printf("Unable to load image %s due to %s\n", filename.c_str(), SDL_GetError());
        SDL_ClearError();
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::Instance()->getRenderer(), tempSurface);
    
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;
    
    if (!texture)
    {
        printf("Unable to create texture from %s due to %s\n", filename.c_str(), SDL_GetError());
        SDL_ClearError();
        return false;
    }
    
    m_textures[textureID] = texture;
    
    return true;
}


#pragma mark - Singleton Instance
TextureManager* TextureManager::Instance()
{
    if (s_pInstance == 0)
    {
        s_pInstance = new TextureManager();
        return s_pInstance;
    }
    
    return s_pInstance;
}

#pragma mark - Constructor and Destructor
TextureManager::~TextureManager()
{
    
}

TextureManager::TextureManager()
{
    
}