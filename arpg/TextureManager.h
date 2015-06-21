//
//  TextureManager.h
//  arpg
//
//  Created by Benjamin Chen on 6/8/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__TextureManager__
#define __arpg__TextureManager__

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "TexturePacker.h"

typedef std::map<std::string,TexturePacker::spriteData> spriteDataMap;

class TextureManager
{
    
public:
    
    void renderTexture(std::string textureID, SDL_Rect* destRect);
    bool loadTexture(std::string filename, std::string textureID);
    bool loadTexturePackerSpriteSheet(std::string spritesheetID, std::string imageFile, std::string dataFile);
    void renderFromSpriteSheet(std::string spriteSheetID, std::string spriteID, SDL_Rect* destRect, SDL_RendererFlip flip = SDL_FLIP_NONE, const double angle = 0.0, SDL_Point* center = NULL);
    //void renderFromSpriteSheet(std::string spriteSheetID, std::string spriteID, SDL_Rect* destRect, bool m_flipX, bool m_flipY, const double angle = 0.0, SDL_Point* center = NULL);
    
    // Public Data Getters
    int getSpriteWidth(std::string spritesheet, std::string spriteID);
    int getSpriteHeight(std::string spritesheet, std::string spriteID);

    // Singleton Instance
    static TextureManager* Instance();
    
private:
    
    // Singleton Static Member
    static TextureManager* s_pInstance;
    
    // Map to hold pointers to textures
    std::map<std::string, SDL_Texture*> m_textures;
    
    // Map to hold Sprite Sheet Data
    std::map<std::string, SDL_Texture*> m_spritesheets;
    std::map<std::string,spriteDataMap> m_spriteDataMaps;
    
    // Spritesheet Image Loader Helper Method
    bool loadSpriteSheet(std::string spritesheetID, std::string imageFile);
    
    // Singleton Private Constructor and Destructor
    TextureManager();
    ~TextureManager();
    
};

#endif /* defined(__arpg__TextureManager__) */
