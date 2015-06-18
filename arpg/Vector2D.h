//
//  Vector2D.h
//  arpg
//
//  Created by Benjamin Chen on 6/15/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#ifndef __arpg__Vector2D__
#define __arpg__Vector2D__

#include <math.h>

class Vector2D
{
    
public:
    
    // Default Constructor
    Vector2D(float x, float y) : m_x(x), m_y(y) {}
    Vector2D() { Vector2D(0,0); }
    
    // Getters and Setters
    float getX() { return m_x; }
    float getY() { return m_y; }
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    
    // Utilities
    float length() { return sqrt(m_x * m_x + m_y * m_y); }
    void normalize();
    
    // Operator overloading for math
    Vector2D operator+(const Vector2D& v2) const;
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
    
    // Multiplication
    Vector2D operator*(float scalar);
    Vector2D& operator*=(float scalar);
    
    // Subtraction
    Vector2D operator-(const Vector2D& v2) const;
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
    
    // Division
    Vector2D operator/(float scalar);
    Vector2D& operator/=(float scalar);
    
    /* Public since the class can be declared private or protected */
    float m_x;
    float m_y;
    
};

#endif /* defined(__arpg__Vector2D__) */
