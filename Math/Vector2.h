#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    float x;
    float y;
    Vector2();
    Vector2(float,float);

    float Magnitude() const;
    float SquareMagnitude() const;
    Vector2 Normalize() const;

    /**
     * \brief Direction from this vector to vector v2
     * \param v2 Target vector
     * \return Direction vector
     */
    Vector2 DirectionTo(const Vector2& v2) const;
    
    
    Vector2 Add(const Vector2& v2) const;
    Vector2 Subtract(const Vector2& v2) const;
    Vector2 Multiply(const float& other) const;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const float& other) const;
    
    Vector2 operator+=(const Vector2& other);
    Vector2 operator-=(const Vector2& other);
    Vector2 operator*=(const float& other);
    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
};

#endif
