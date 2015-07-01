//
//  Strider.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/17/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <sstream>

#include "GameManager.h"
#include "TextureManager.h"
#include "Strider.h"

#pragma mark - Update Loop Methods
void Strider::draw()
{
    TextureManager::Instance()->renderFromSpriteSheet(m_spritesheet, m_currentSpriteID, &m_boundingBox, m_flip);
    
    // void renderFromSpriteSheet(std::string spriteSheetID, std::string spriteID, SDL_Rect* destRect, SDL_RendererFlip flip = SDL_FLIP_NONE, const double angle = 0.0, SDL_Point* center = NULL);
    
    /* Debug drawing of bounding box */
    debug_render_color(0, 255, 0, 100);
    debug_sdl_rect(m_boundingBox);
    
    /* Debug Drawing of Hit Boxes */
    debug_render_color(0, 0, 255, 100);
    debug_sdl_rect(m_attackBoundingBox);
}

void Strider::update()
{
    handleState();
    updateAnimationFrame();
    updateBoundingBox();
}

void Strider::handleInput(SDL_Event *event)
{
    /* Stop accepting input if */
    if (m_currentState == kStateForwardSlashAttack)
    {
        return;
    }
    
    m_velocity = {0,0};
    bool walking = false;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if (currentKeyStates[SDL_SCANCODE_U])
    {
        changeState(kStateForwardSlashAttack);
        return;
    }
    
    /* Walking up has precedence over walking down */
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() - 1);
    }
    else if (currentKeyStates[SDL_SCANCODE_S])
    {
        walking = true;
        m_velocity.setY(m_velocity.getY() + 1);
    }
    
    /* Walking right has precedence over walking left */
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        if (m_flip != SDL_FLIP_NONE)
        {
            /* Temporary terribleness */
            m_flip = SDL_FLIP_NONE;
            m_position.setX(m_position.getX() - m_boundingBox.w);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() + 1);
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        if (m_flip != SDL_FLIP_HORIZONTAL)
        {
            /* Temporary terribleness */
            m_flip = SDL_FLIP_HORIZONTAL;
            m_position.setX(m_position.getX() + m_boundingBox.w);
        }
        walking = true;
        m_velocity.setX(m_velocity.getX() - 1);
    }
    
    if (walking)
    {
        changeState(kStateWalking);
    }
    else
    {
        changeState(kStateIdle);
    }
}

#pragma mark - State Management Methods
void Strider::changeState(GameObjectState newState)
{
    switch (newState)
    {
        case kStateIdle:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateIdle");
                m_currentState = newState;
                m_currentAnimation = "strider_idle_animation";
                m_currentAnimationFrame = -1;
            }
            break;
            
        case kStateWalking:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateWalking");
                m_currentState = newState;
                m_currentAnimation = "strider_walking_animation";
                m_currentAnimationFrame = 0;
            }
            break;
            
        case kStateForwardSlashAttack:
            if (m_currentState != newState)
            {
                debug_print("%s\n", "Changing to State: kStateForwardSlashAttack");
                m_currentState = newState;
                m_currentAnimation = "strider_fslash_animation";
                m_currentAnimationFrame = -1;
            }
            
        default:
            break;
    }
}

void Strider::handleState()
{
    switch (m_currentState)
    {
        case kStateIdle:
            idleState();
            break;
            
        case kStateWalking:
            walkingState();
            break;
            
        case kStateForwardSlashAttack:
            fslashState();
            break;
            
        default:
            break;
    }
}

void Strider::walkingState()
{
    m_currentAnimationFrame += 1;
    
    /* Normalize velocity */
    m_velocity.normalize();
    
    /* Calculate walking speed per frame */
    m_velocity *= m_walkingSpeed;
    
    /* Apply to position */
    m_position += m_velocity;
}

void Strider::idleState()
{
    m_currentAnimationFrame += 1;
}

void Strider::fslashState()
{
    m_currentAnimationFrame += 1;
    //updateBoundingBox();
    
    int x, y, w, h;
    
    if (m_flip == SDL_FLIP_HORIZONTAL)
    {
        w = m_boundingBox.w - 25;
        x = m_boundingBox.x + m_boundingBox.w - w - 25;
        y = m_boundingBox.y;
        h = m_boundingBox.h / 2;
    }
    else
    {
        x = m_boundingBox.x + 25;
        y = m_boundingBox.y;
        w = m_boundingBox.w - 25;
        h = m_boundingBox.h / 2;
    }
    
    m_attackBoundingBox = {x,y,w,h};
    
    /* Completed Slashing Animation */
    if (m_currentAnimationFrame == m_animations["strider_fslash_animation"].size())
    {
        changeState(kStateIdle);
        m_attackBoundingBox = {0,0,0,0};
    }
}

# pragma mark - Animation Helper Methods
void Strider::updateAnimationFrame()
{
    if (m_currentAnimationFrame >= m_animations[m_currentAnimation].size())
    {
        m_currentAnimationFrame = 0;
    }
    else
    {
        setCurrentSpriteID(m_animations[m_currentAnimation][m_currentAnimationFrame]);
    }
}

/* Temporary method until data bound constructor can be build */
void Strider::registerAnimations()
{
    /* Vector of animation frame names */
    std::vector<std::string> idleAnimationFrames;
    
    /* Start of the idle animation keys */
    std::string idle = "strider_idle_";
    
    for (int i = 1; i < 20; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << idle << 0 << i;
        }
        else
        {
            stream << idle << i;
        }
        /* Number of frames each animation plays for */
        for (int j = 0; j < 6; j++)
        {
            idleAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_idle_animation"] = idleAnimationFrames;
    
    /* Vector of walking animation frames */
    std::vector<std::string> walkingAnimationFrames;
    
    std::string walking = "strider_walking_";
    
    for (int i = 1; i < 11; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << walking << 0 << i;
        }
        else
        {
            stream << walking << i;
        }
        for (int j = 0; j < 6; j++)
        {
            walkingAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_walking_animation"] = walkingAnimationFrames;
    
    /* Vector of fslash animation frames */
    std::vector<std::string> fslashAnimationFrames;
    
    std::string fslash = "strider_fslash_";
    
    for (int i = 1; i < 12; i++)
    {
        std::stringstream stream;
        if (i < 10)
        {
            stream << fslash << 0 << i;
        }
        else
        {
            stream << fslash << i;
        }
        for (int j = 0; j < 3; j++)
        {
            fslashAnimationFrames.push_back(stream.str());
        }
    }
    
    m_animations["strider_fslash_animation"] = fslashAnimationFrames;
}

#pragma mark - Lifecycle Methods
void Strider::clean()
{
    /* Stub Method */
}

void Strider::init()
{
    m_boundingBox = {0,0,0,0};
    m_gameObjectType = kPlayerObject;
    m_spritesheet = "strider";
    m_currentSpriteID = "";
    m_position = {0,0};
    m_walkingSpeed = 1.0;
    m_attackBoundingBox = {0,0,0,0};
    
    registerAnimations();
    changeState(kStateIdle);
}