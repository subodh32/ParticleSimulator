#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include "Structure.h"

Structure::Structure() {
    
}

Structure::~Structure() {
    
}

std::vector<Particle*> Structure::getParticles() const
{
    return particles;
}

void Structure::addParticle(int index, Particle *p)
{
    particles.push_back(p);
}

void Structure::addLink(int p1, int p2, float seperation_dist)
{
    links.push_back(std::make_tuple(particles[p1], particles[p2], seperation_dist));
}

void Structure::update(float dt)
{
    for(auto link : links)
    {
        link_particles(*std::get<0>(link), *std::get<1>(link), std::get<2>(link));
    }
}

void Structure::link_particles(Particle& p1, Particle& p2, float seperation_dist)
{
    Vector2D normal = p1.getPosition() - p2.getPosition();
    float distance = normal.magnitude();

    normal = normal.normalize();
    Vector2D seperation = normal * 0.5f * (distance - seperation_dist);

    DrawLine(p1.getPosition().getX(), p1.getPosition().getY(), p2.getPosition().getX(), p2.getPosition().getY(), BLACK);

    if(distance < seperation_dist)
    {
        p1.setPosition(p1.getPosition() - seperation);
        p2.setPosition(p2.getPosition() + seperation);
    }
    else if(distance > seperation_dist)
    {
        p1.setPosition(p1.getPosition() - seperation);
        p2.setPosition(p2.getPosition() + seperation);
    }
}