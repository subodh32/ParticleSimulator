#include <iostream>
#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D()
    : x(0.0f), y(0.0f) {}

Vector2D::Vector2D(float x = 0.0f, float y = 0.0f)
    : x(x), y(y) {}

// Getters and setters
float Vector2D::getX() const { return x; }
float Vector2D::getY() const { return y; }
void Vector2D::setX(float newX) { x = newX; }
void Vector2D::setY(float newY) { y = newY; }

// set all values
void Vector2D::set(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
}

// Vector2D operations
Vector2D Vector2D::operator+(const Vector2D &other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

float Vector2D::operator*(const Vector2D &other) const
{
    return x * other.x + y * other.y;
}

Vector2D Vector2D::operator%(const Vector2D &other) const
{
    return Vector2D(y * other.x - x * other.y, x * other.y - y * other.x);
}

float Vector2D::magnitude() const
{
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const
{
    float mag = magnitude();
    return Vector2D(x / mag, y / mag);
}

Vector2D Vector2D::print() const
{
    std::cout << "(" << x << ", " << y << ")\n";
    return *this;
}

// Destructor
Vector2D::~Vector2D()
{
    
}