#include "Vector2.h"
#include <iostream>

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector2::Magnitude() const
{
    return sqrtf(x * x + y * y);
}

float Vector2::SquareMagnitude() const
{
    return (x * x + y * y);
}

Vector2 Vector2::Normalize() const
{
    auto magnitude = Magnitude();
    if(magnitude != 0)
    {
        return Vector2(x/ magnitude, y / magnitude);
    }
    return Vector2(0,0);
}

Vector2 Vector2::DirectionTo(const Vector2& v2) const
{
    return Vector2(v2.x - x, v2.y - y);
}



Vector2 Vector2::Add(const Vector2& other) const
{
    return Vector2(x + other.x,y + other.y);
}

Vector2 Vector2::Subtract(const Vector2& v2) const
{
    return Vector2(x - v2.x, y - v2.y);
}

Vector2 Vector2::Multiply(const float& other) const
{
    return Vector2(x * other, y * other);
}


Vector2 Vector2::operator+(const Vector2& other) const
{
    return Add(other);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Subtract(other);
}


Vector2 Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator*(const float& other) const
{
    return Multiply(other);
}

Vector2 Vector2::operator*=(const float& other)
{
    x *= other;
    y *= other;
    return (*this);
}
bool Vector2::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !(*this == other);
}






