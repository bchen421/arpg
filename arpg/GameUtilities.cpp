//
//  GameUtilities.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/25/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "GameUtilities.h"

GameUtilities::CornersOfRect GameUtilities::getCornersOfRect(SDL_Rect* rect)
{
    GameUtilities::CornersOfRect corners;
    
    corners.topLeft = {float(rect->x), float(rect->y)};
    corners.topRight = {float(rect->x + rect->w), float(rect->y)};
    corners.bottomLeft = {float(rect->x), float(rect->y + rect->h)};
    corners.bottomRight = {float(rect->x + rect->w), float(rect->y + rect->h)};
    
    return corners;
}
