//
//  TexturePacker.h
//  arpg
//
//  Created by Benjamin Chen on 6/12/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__TexturePacker__
#define __arpg__TexturePacker__

#include <string>
#include <map>
#include <SDL2/SDL.h>

#include "rapidjson/document.h"

class TexturePacker
{
    
public:
    
    struct spriteData {
        SDL_Rect frame;
        int spriteWidth;
        int spriteHeight;
        bool rotated;
        bool trimmed;
    };
    
    static bool parseSpritesheetData(std::string filename, std::map<std::string,TexturePacker::spriteData>& map);
    
private:
    
    static bool getFileContents(std::string filename, std::string* contents);
    static bool validateSpritesheetJSON(rapidjson::Document* document);
    
};

#endif /* defined(__arpg__TexturePacker__) */
