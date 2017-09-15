//
//  UnitTests.cpp
//  arpg
//
//  Created by Benjamin Chen on 7/3/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <gtest/gtest.h>

#include "GameUtilities.h"

TEST(GameUtilitiesCornersOfRect, topLeft ) {
    SDL_Rect rect = {5,10,8,16};
    GameUtilities::CornersOfRect corners;
    corners = GameUtilities::getCornersOfRect(&rect);
    EXPECT_EQ(5, corners.topLeft.getX());
    EXPECT_EQ(10, corners.topLeft.getY());
}

TEST(GameUtilitiesCornersOfRect, topRight ) {
    SDL_Rect rect = {5,10,8,16};
    GameUtilities::CornersOfRect corners;
    corners = GameUtilities::getCornersOfRect(&rect);
    EXPECT_EQ(13, corners.topRight.getX());
    EXPECT_EQ(10, corners.topRight.getY());
}

TEST(GameUtilitiesCornersOfRect, bottomLeft ) {
    SDL_Rect rect = {5,10,8,16};
    GameUtilities::CornersOfRect corners;
    corners = GameUtilities::getCornersOfRect(&rect);
    EXPECT_EQ(5, corners.bottomLeft.getX());
    EXPECT_EQ(26, corners.bottomLeft.getY());
}

TEST(GameUtilitiesCornersOfRect, bottomRight ) {
    SDL_Rect rect = {5,10,8,16};
    GameUtilities::CornersOfRect corners;
    corners = GameUtilities::getCornersOfRect(&rect);
    EXPECT_EQ(13, corners.bottomRight.getX());
    EXPECT_EQ(26, corners.bottomRight.getY());
}

TEST(GameUtilitiesTransformChildRect, noFlip)
{
    SDL_Rect parentRect = {100,200,50,75};
    SDL_Rect childRect = {5,10,15,20};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    GameUtilities::transformChildRect(&parentRect, &childRect, &flip);
    
    EXPECT_EQ(105, childRect.x);
    EXPECT_EQ(210, childRect.y);
    EXPECT_EQ(15, childRect.w);
    EXPECT_EQ(20, childRect.h);
}

TEST(GameUtilitiesTransformChildRect, horizontalFlip)
{
    SDL_Rect parentRect = {100,200,50,75};
    SDL_Rect childRect = {5,10,15,20};
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    GameUtilities::transformChildRect(&parentRect, &childRect, &flip);
    
    EXPECT_EQ(130, childRect.x);
    EXPECT_EQ(210, childRect.y);
    EXPECT_EQ(15, childRect.w);
    EXPECT_EQ(20, childRect.h);
}

