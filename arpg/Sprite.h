//
//  Sprite.h
//  arpg
//
//  Created by Benjamin Chen on 6/7/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Sprite__
#define __arpg__Sprite__

#include <string>

#include "GameObject.h"

class Sprite : public GameObject
{
    
public:
    
    /* Update loop */
    virtual void draw()=0;
    virtual void update()=0;
    
    /* Lifecycle */
    virtual void clean()=0;
    virtual void init()=0;
    
    /* Getter */
    Vector2D getPosition() { return m_position; }
    SDL_RendererFlip getFlip() { return m_flip; }
    
    /* Polymorphic Destructor */
    virtual ~Sprite() {}
    
protected:
    
    /* Hitbox and Hurtbox management */
    void clearHitboxes() { m_hitboxes.clear(); };
    void clearHurtboxes() { m_hurtboxes.clear(); };
    void addHitbox(SDL_Rect hitbox) { m_hitboxes.push_back(hitbox); }
    void addHurtbox(SDL_Rect hurtbox) { m_hurtboxes.push_back(hurtbox); }
    void updateHitboxes();
    void updateHurtboxes();
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState)=0;
    
    /*
     * Wrapper to set the current spriteID and then
     * update width and height of m_boundingBox
     */
    virtual void setCurrentSpriteID(std::string spriteID);
    
    /* Updates Bounding Box with (x,y) from m_position */
    virtual void updateBoundingBox();
    
    /* Spritesheet key to render spriteID from */
    std::string m_spritesheet;
    
    /*
     * Current spriteID use to query map of textures.
     * This should be set using setCurrentSpriteID() to ensure
     * that m_boundingBox has the current width and height
     */
    std::string m_currentSpriteID;
    
    /* 
     * Member bool to handle direction facing and flipping
     * Temporarily keeping as SDL_Flip, until code for horizontal and vertical
     * flipping is done.
     */
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;
    
    /* Hitbox and Hurtbox Containers */
    std::vector<SDL_Rect> m_hitboxes;
    std::vector<SDL_Rect> m_hurtboxes;
    
};

#endif /* defined(__arpg__Sprite__) */
