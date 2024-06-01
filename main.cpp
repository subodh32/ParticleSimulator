#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "raylib.h"
#include "Particle.h"
#include "Globals.h"
#include "Structure.h"

void link_particles(Particle &p1, Particle &p2, float seperation_dist);
void on_mouse_click(Particle *p, Vector2D mousePos, float mouse_force);

int main()
{

    float dt = 1.0f / 60.0f;

    const int screenWidth = WorldWidth;
    const int screenHeight = WorldHeight;

    // Particle P1(Vector2D(100.0f, 100.0f),Vector2D(0,1000), 10.0f);

    int numParticles = 10;
    float mouse_force = 4000.0f;

    // Particle particles[numParticles];
    std::vector<Particle*> particles(numParticles);

    // chain
    for (int i = 0; i < numParticles; i++)
    {
        // particles[i] = Particle(Vector2D(0.0f, 100.0f), 10.0f);
        // particles at random positions
        Particle *p = new Particle(Vector2D(50 + (50 * i), 50), 15.0f);
        particles[i] = p;
        (*particles[i]).setDefaultColor(RED);
        (*particles[i]).setColor(RED);
    }

    Structure car;
    for (int i = 0; i <= 3; i++)
    {
        Particle *p = new Particle(Vector2D(50 + (50 * i), 50), 10.0f);
        car.addParticle(i, p);
    }

    car.addLink(0, 1, 50.0f);
    car.addLink(1, 2, 50.0f);
    car.addLink(2, 3, 50.0f);
    car.addLink(0,3,50.0f);
    car.addLink(0,2,70.711f);

    for(auto p : car.getParticles())
    {
        particles.push_back(p);
    }

    InitWindow(screenWidth, screenHeight, "Raylib Window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        // link_particles(particles[0], particles[1], 50.0f);
        // link_particles(particles[1], particles[2], 50.0f);

        for (int i = 0; i < numParticles - 1; i++)
        {
            link_particles(*particles[i], *particles[i + 1], 50.0f);
        }

        // on mouse click get mouse position and apply force to particle

        // on mouse wheel move change mouse_force proportionsally
        mouse_force += GetMouseWheelMove() * 100.0f;
        // display mouse_force
        DrawText(TextFormat("Force: %f", mouse_force), 10, 30, 20, BLACK);

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(MOUSE_BUTTON_MIDDLE))
        {
            // add new particle at mouse position
            Vector2D mousePos;
            mousePos.setX(GetMouseX());
            mousePos.setY(GetMouseY());

            Particle *p = new Particle(mousePos, 10.0f);
            particles.push_back(p);
        }

        // update and draw particles

        car.update(dt);
        // car.draw();

        for (int i = 0; i < particles.size(); i++)
        {
            on_mouse_click( particles[i], Vector2D(GetMouseX(), GetMouseY()), mouse_force);
            (*particles[i]).update(dt);
            (*particles[i]).draw();

            for (int j = i + 1; j < particles.size(); j++)
            {
                (*particles[i]).ParticleCollision(*particles[j]);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void link_particles(Particle &p1, Particle &p2, float seperation_dist)
{
    Vector2D normal = p1.getPosition() - p2.getPosition();
    float distance = normal.magnitude();

    normal = normal.normalize();
    Vector2D seperation = normal * 0.5f * (distance - seperation_dist);

    DrawLine(p1.getPosition().getX(), p1.getPosition().getY(), p2.getPosition().getX(), p2.getPosition().getY(), BLACK);

    if (distance < seperation_dist)
    {
        p1.setPosition(p1.getPosition() - seperation);
        p2.setPosition(p2.getPosition() + seperation);
    }
    else if (distance > seperation_dist)
    {
        p1.setPosition(p1.getPosition() - seperation);
        p2.setPosition(p2.getPosition() + seperation);
    }
}

void on_mouse_click(Particle *particle, Vector2D mousePos, float mouse_force)
{
    Particle p = *particle;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2D mousePos;
        mousePos.setX(GetMouseX());
        mousePos.setY(GetMouseY());

        if (p.isSelected())
        {
            Vector2D force = (mousePos - p.getPosition()).normalize() * mouse_force;
            p.setForce(force);
        }
    }
    else
    {
        p.setForce(Vector2D(0, Gravity));
    }

    // on mouse click select particle
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        Vector2D mousePos;
        mousePos.setX(GetMouseX());
        mousePos.setY(GetMouseY());

        if ((mousePos - p.getPosition()).magnitude() < p.getRadius())
        {
            if (p.isSelected())
            {
                p.setSelected(false);
                p.setColor(p.getDefaultColor());
            }
            else
            {
                p.setSelected(true);
                p.setColor(GREEN);
            }
        }
    }

    *particle = p;
}