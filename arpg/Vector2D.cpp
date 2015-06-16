//
//  Vector2D.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/15/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include "Vector2D.h"

void Vector2D::normalize()
{
    float len = length();
    
    if (len > 0)
    {
        (*this) *= (1 / len);
    }
}

#pragma mark - Overload Math Operators
/* Addition */
Vector2D Vector2D::operator+(const Vector2D& v2) const
{
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;
    
    return v1;
}

/* Multiplication */
Vector2D Vector2D::operator*(float scalar)
{
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    
    return *this;
}

/* Subtraction */
Vector2D Vector2D::operator-(const Vector2D& v2) const
{
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;
    
    return v1;
}

/* Division */
Vector2D Vector2D::operator/(float scalar)
{
    return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    
    return *this;
}
