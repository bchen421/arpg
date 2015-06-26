//
//  GameObject.h
//  arpg
//
//  Created by Benjamin Chen on 6/9/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef arpg_GameObject_h
#define arpg_GameObject_h

#include <SDL2/SDL.h>

#include "Constants.h"
#include "GameUtilities.h"
#include "Vector2D.h"

class GameObject
{
    
public:
    
    /* Update loop */
    virtual void draw()=0;
    virtual void update()=0;
    
    /* Lifecycle */
    virtual void clean()=0;
    virtual void init()=0;
    
    /* State Changing Interface */
    virtual void changeState(GameObjectState newState)=0;
    
    /* Public Getters */
    SDL_Rect getBoundingBox() { return m_boundingBox; }
    GameObjectType getGameObjectType() { return m_gameObjectType; }
    GameObjectState getGameObjectState() { return m_currentState; }
    Vector2D getPosition() { return m_position; }
    
    /* Public Setters */
    void setPosition(Vector2D position) { m_position = position; }
    
    /* Destructor */
    virtual ~GameObject(){}
    
protected:

    /* Bounding Box of the Object on the screen */
    SDL_Rect m_boundingBox;
    
    /* Position of GameObject.  Vector so it can do proper Vector math */
    Vector2D m_position;
    
    /* Enumeration of the objects current state */
    GameObjectState m_currentState = kStateNone;
    
    /* Enumeration to identify objects of different types */
    GameObjectType m_gameObjectType = kGameObject;
        
};

#endif
