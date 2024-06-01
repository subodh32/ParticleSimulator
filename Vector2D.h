#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {

private:
    float x;
    float y;

public:
    // Constructors
    Vector2D();
    Vector2D(float x, float y);

    // Destructor
    ~Vector2D();

    // Getters and Setters
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

    void set(float newX, float newY, float newZ);

    // Vector operations
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    float operator*(const Vector2D& other) const;
    Vector2D operator%(const Vector2D& other) const;

    // Other utility functions
    float magnitude() const;
    Vector2D normalize() const;
    Vector2D print() const;
};

#endif // VECTOR2D_H