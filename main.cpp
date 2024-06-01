#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "raylib.h"
#include "Particle.h"
#include "Globals.h"

void link_particles(Particle& p1, Particle& p2, float seperation_dist);

int main() {

    float dt = 1.0f / 60.0f;

    const int screenWidth = WorldWidth;
    const int screenHeight = WorldHeight;

    // Particle P1(Vector2D(100.0f, 100.0f),Vector2D(0,1000), 10.0f);

    int numParticles = 3;

    // Particle particles[numParticles];
    std::vector<Particle> particles(numParticles);

    for (int i = 0; i < numParticles; i++)
    {
        // particles[i] = Particle(Vector2D(0.0f, 100.0f), 10.0f);
        //particles at random positions
        particles[i] = Particle(Vector2D(50 + (10*i), 50), 15.0f);
    }

    particles[0].setColor(RED); 
    particles[1].setColor(RED);
    particles[2].setColor(RED);

    particles[0].setPosition(Vector2D(100, 150));
    particles[1].setPosition(Vector2D(100, 100));
    particles[2].setPosition(Vector2D(100, 50));

    particles[0].setLastPosition(particles[0].getPosition());
    particles[1].setLastPosition(particles[1].getPosition());
    particles[2].setLastPosition(particles[2].getPosition());

    InitWindow(screenWidth, screenHeight, "Raylib Window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        link_particles(particles[0], particles[1], 50.0f);
        link_particles(particles[1], particles[2], 50.0f);
        link_particles(particles[2], particles[0], 50.0f);
        
        //on mouse click get mouse position and apply force to particle
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2D mousePos;
            mousePos.setX(GetMouseX());
            mousePos.setY(GetMouseY());

            for (int i = 0; i < particles.size(); i++)
            {
                Vector2D force = (mousePos - particles[i].getPosition()).normalize() * 100.0f;
                particles[i].setForce(force);
            }
        }
        else{
            for (int i = 0; i < particles.size(); i++)
            {
                particles[i].setForce(Vector2D(0, Gravity));
            }
        }

        if(IsKeyPressed(KEY_ENTER)){
            //add new particle at mouse position
            Vector2D mousePos;
            mousePos.setX(GetMouseX());
            mousePos.setY(GetMouseY());

            particles.push_back(Particle(mousePos, 10.0f));
        }

        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].update(dt);
            particles[i].draw();

            for (int j = i + 1; j < particles.size(); j++)
            {
                particles[i].ParticleCollision(particles[j]);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void link_particles(Particle& p1, Particle& p2, float seperation_dist)
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