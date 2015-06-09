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

class TextureManager
{
    
public:
    
    void renderTexture(std::string textureID, SDL_Rect* destRect);
    bool loadTexture(std::string filename, std::string textureID);

    // Singleton Instance
    static TextureManager* Instance();
    
private:
    
    // Singleton Static Member
    static TextureManager* s_pInstance;
    
    // Map to hold pointer to textures
    std::map<std::string, SDL_Texture*> m_textures;
    
    // Singleton Private Constructor and Destructor
    TextureManager();
    ~TextureManager();
    
};



#endif /* defined(__arpg__TextureManager__) */
