#include "Vector2D.h"
#include "raylib.h"
#include "Particle.h"
#include "Globals.h"

Particle::Particle()
    : position(Vector2D()), radius(0.0f) {
        lastPosition = position;
        acceleration = Vector2D(0,Gravity);
    }

Particle::Particle(Vector2D pos, float rad)
    : position(pos), radius(rad) {
        lastPosition = position;
        acceleration = Vector2D(0,Gravity);
    }

Particle::Particle(Vector2D pos, float rad, Color color){
    position = pos;
    radius = rad;
    lastPosition = position;
    acceleration = Vector2D(0,Gravity);
    defaultColor = color;
    currentColor = color;
}

Particle::Particle(Vector2D pos, Vector2D acc, float rad)
    : position(pos), acceleration(acc), radius(rad) {
        lastPosition = position;
    }

Particle::~Particle() {}

Vector2D Particle::getPosition() const { return position; }
Vector2D Particle::getAcceleration() const { return acceleration; }
float Particle::getRadius() const { return radius; }

void Particle::setPosition(Vector2D pos) { position = pos; }
void Particle::setAcceleration(Vector2D acc) { acceleration = acc; }
void Particle::setRadius(float rad) { radius = rad; }
void Particle::setLastPosition(Vector2D lastPos) { lastPosition = lastPos; }

void Particle::update(float dt)
{
    Vector2D temp = position;
    position = (position*2) - lastPosition + acceleration * dt * dt;
    lastPosition = temp;

    //check for collision with the all sides of the window
    if (position.getY() > WorldHeight - radius)
    {
        position.setY(WorldHeight - radius);
        lastPosition.setY(position.getY() + (position.getY() - lastPosition.getY()) * BounceFactorFloor);
    }

    if (position.getY() < radius)
    {
        position.setY(radius);
        lastPosition.setY(position.getY() + (position.getY() - lastPosition.getY()) * BounceFactorFloor);
    }

    if (position.getX() > WorldWidth - radius)
    {
        position.setX(WorldWidth - radius);
        lastPosition.setX(position.getX() + (position.getX() - lastPosition.getX()) * BounceFactorFloor);
    }

    if (position.getX() < radius)
    {
        position.setX(radius);
        lastPosition.setX(position.getX() + (position.getX() - lastPosition.getX()) * BounceFactorFloor);
    }
}

void Particle::draw() const
{
    DrawCircle(position.getX(), position.getY(), radius, currentColor);

    //draw the acceleration vector
    // DrawLine(position.getX(), position.getY(), position.getX() + acceleration.getX(), position.getY() + acceleration.getY(), RED);
}

void Particle::applyForce(Vector2D force)
{
    acceleration = acceleration + force;
}

void Particle::setForce(Vector2D force)
{
    acceleration = force;
}

void Particle::ParticleCollision(Particle& other)
{
    Vector2D normal = position - other.getPosition();
    float distance = normal.magnitude();
    float overlap = radius + other.getRadius() - distance;

    if (overlap > 0)
    {
        normal = normal.normalize();
        Vector2D separation = normal * overlap * 0.5f;

        position = position + separation;
        other.setPosition(other.getPosition() - separation);
    }
}