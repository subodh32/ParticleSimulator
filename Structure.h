#include <vector>
#include "Vector2D.h"
#include "raylib.h"
#include "Particle.h"

class Structure{
private:
    std::vector<std::tuple<Particle*, Particle*, float>> links;

    void link_particles(Particle& p1, Particle& p2, float seperation_dist);

public:
    std::vector<Particle*> particles;

    Structure();
    ~Structure();

    std::vector<Particle*> getParticles() const;

    void addParticle(int index,Particle *p);
    void addLink(int p1, int p2, float seperation_dist);

    void update(float dt);
};