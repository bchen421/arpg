//
//  State.h
//  arpg
//
//  Created by Benjamin Chen on 7/1/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__State__
#define __arpg__State__

/* Component of Player Class */
class Player;

#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "Vector2D.h"

class State
{
    
public:
    
    /* Polymorphic Destructor */
    virtual ~State() { m_player = NULL; }
    
    virtual void init(Player* player)=0;
    virtual void onEnter()=0;
    virtual void handleInput(SDL_Event* event)=0;
    virtual void update()=0;
    virtual void onExit()=0;
    
    /* Getters */
    std::string getCurrentSpriteID() { return m_currentSpriteID; }
    std::string getCurrentAnimation() { return m_currentAnimation; }
    
protected:
    
    /* Player Setters */
    void updatePlayerBoundingBox();
    void setPlayerSpriteID(std::string spriteID);
    void setPlayerPosition(Vector2D position);
    void setPlayerFlip(SDL_RendererFlip flip);
    void setPlayerState(GameObjectState newState);
    
    /* Temp Utility Method to Load in Animation Frames */
    virtual void registerAnimations()=0;
    
    /* Helper Methods */
    virtual void updateAnimationFrame()=0;
    
    /* Pointer to Owning Player Object */
    Player* m_player;
    
    /* Local Representation of Player Attributes for Setting */
    std::string m_currentSpriteID;
    std::string m_currentAnimation;
    int m_currentFrame;
    std::map<std::string,std::vector<std::string>> m_animations;
    Vector2D m_velocity;
    
};

#endif /* defined(__arpg__State__) */
