#include <strings.h>
#include "core.h"

particle* particles = NULL;
int particles_length = 0;
int particles_size = 0;
int particles_num = 0;
int particles_cap = 1000;

well* wells = NULL;
int wells_length = 0;
int wells_size = 0;
int wells_num = 0;

generator* generators = NULL;
int generators_length = 0;
int generators_size = 0;
int generators_num = 0;

metaForce* metaForces = NULL;
int metaForces_length = 0;
int metaForces_size = 0;
int metaForces_num = 0;

int addParticle()
{
    // Add to the particle_num
    ++particles_num;

    // Look for an unused particle
    int i;
    for (i = 0; i < particles_length; ++i)
    {
        // Check to see if the particle is active
        if (particles[i].active == 0)
        {
            // Clear the particle
            memset(particles + i, 0, sizeof(particle));

            // Return it
            return i;
        }
    }

    // If we couldn't find an inactive one, add a new particle
    addItem((void**)&particles, &particles_length, &particles_size, 5000, NULL, sizeof(particle));

    // Set it to active
    particles[particles_length - 1].active = 1;

    return particles_length - 1;
}

void remParticle(int zindex)
{
    // Remove the specified particle
    particles[zindex].active = 0;

    // Subtract from the particle_num
    --particles_num;
}

int addWell()
{
    // Add a new well
    addItem((void**)&wells, &wells_length, &wells_size, 5, NULL, sizeof(well));

    // Increment the number of wells
    ++wells_num;

    return wells_length - 1;
}

void remWell(int zindex)
{
    // Remove the specified well
    removeItem(wells, &wells_length, zindex, sizeof(well));

    // Decrement the number of wells
    --wells_num;
}

int addGenerator()
{
    // Add a new well
    addItem((void*)&generators, &generators_length, &generators_size, 5, NULL, sizeof(generator));

    // Increment the number of generators
    ++generators_num;

    return generators_length - 1;
}

void remGenerator(int zindex)
{
    // Remove the specified well
    removeItem((void**)&generators, &generators_length, zindex, sizeof(generator));

    // Decrement the number of generators
    --generators_num;
}

int addMetaForce()
{
    // Add a new well
    addItem((void*)&metaForces, &metaForces_length, &metaForces_size, 5, NULL, sizeof(metaForce));

    // Increment the number of generators
    ++metaForces_num;

    return metaForces_length - 1;
}

void remMetaForce(int zindex)
{
    // Remove the specified well
    removeItem((void**)&metaForces, &metaForces_length, zindex, sizeof(metaForces));

    // Decrement the number of generators
    --metaForces_num;
}
