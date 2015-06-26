//
//  GameUtilities.h
//  arpg
//
//  Created by Benjamin Chen on 6/25/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__GameUtilities__
#define __arpg__GameUtilities__

#include <SDL2/SDL.h>
#include "Vector2D.h"

/* Debugging Mode */
#define LOCALDEBUG 1

#define debug_print(fmt, ...) \
do { if (LOCALDEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
__LINE__, __func__, __VA_ARGS__); } while (0)

#define debug_render_color(r, g, b, a) \
do { if (LOCALDEBUG) SDL_SetRenderDrawColor(GameManager::Instance()->getRenderer(), \
r, g, b, a); } while (0)

#define debug_sdl_rect(rect) \
do { if (LOCALDEBUG) SDL_RenderFillRect(GameManager::Instance()->getRenderer(), \
&rect); } while (0)

class GameUtilities
{
    
public:
    
    /* Structure of Vector2Ds for easy vector math */
    struct  CornersOfRect {
        Vector2D topLeft;
        Vector2D topRight;
        Vector2D bottomLeft;
        Vector2D bottomRight;
    };
    
    /*
     * Convenience Static Method used to get the corners of an SDL_Rect
     * as Vector2Ds for easy vector math.  SDL_Rect is passed by reference
     */
    static CornersOfRect getCornersOfRect(SDL_Rect* rect);
    
};

#endif /* defined(__arpg__GameUtilities__) */
