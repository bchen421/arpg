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

