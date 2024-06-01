#ifndef PARTICLE_H
#define PARTICLE_H

// #include "raylib.h"

class Particle {
private:
    Vector2D position;
    Vector2D lastPosition;
    Vector2D acceleration;
    float radius;

    Color defaultColor = BLUE;
    Color  currentColor = BLUE;
    bool selected = false;

public:
    Particle();
    Particle(Vector2D pos, float rad);
    Particle(Vector2D pos, Vector2D acc, float rad);

    ~Particle();

    Vector2D getPosition() const;
    Vector2D getAcceleration() const;
    float getRadius() const;

    void setPosition(Vector2D pos);
    void setAcceleration(Vector2D acc);
    void setRadius(float rad);
    void setLastPosition(Vector2D lastPos);

    void setColor(Color color) { currentColor = color; }
    Color getColor() const { return currentColor; }

    void setDefaultColor(Color color) { defaultColor = color; }
    Color getDefaultColor() const { return defaultColor; }

    void setSelected(bool sel) { selected = sel; }
    bool isSelected() const { return selected; }

    void update(float dt);
    void draw() const;

    void applyForce(Vector2D force);
    void setForce(Vector2D force);

    void ParticleCollision(Particle& other);
};


#endif