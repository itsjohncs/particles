#include "auxiliary/math+.h"
#include "items.h"

float friction = 0.99;

void step(int zwidth, int zheight, int ztime)
{
    // A bit primitive but can't get a much better effect going piece by piece.
    int t;
    for (t = 0; t < ztime; ++t)
    {
        // The "gravity constant"
        const float k = 0.1;

        // First let the generators create any particles
        int i;
        for (i = 0; i < generators_length; ++i)
        {
            // Is it time to generate?
            if (--generators[i].countdown <= 0)
            {
                // If we can make another particle
                if (particles_num < particles_cap)
                {
                    // Create a new particle
                    int newParticle = addParticle();

                    // Set it to active
                    particles[newParticle].active = 1;

                    // Set its color components
                    particles[newParticle].alpha = 20;
                    particles[newParticle].color = rgb(randInUI(0, 255), randInUI(0, 255), randInUI(0, 255));

                    // Set the particle's position to be right on top of the generator
                    particles[newParticle].x = generators[i].x + randInF(-generators[i].radius, generators[i].radius);
                    particles[newParticle].y = generators[i].y + randInF(-generators[i].radius, generators[i].radius);

                    // Set the particle's size
                    particles[newParticle].radius_min = 0;
                    particles[newParticle].radius_max = 2;

                    // Set the particle's initial velocity
                    particles[newParticle].vx = generators[i].vx;
                    particles[newParticle].vy = generators[i].vy;

                    // Reset the generator's countdown
                    generators[i].countdown = generators[i].countdown_max;
                } else break;
            }
        }


        // Then let the wells work their magic on the particles
        for (i = 0; i < wells_length; ++i)
        {
            int j;
            for (j = 0; j < particles_length; ++j)
            {
                // Ignore the particle if its inactive
                if (particles[j].active == 0) continue;

                // Find the distance squared between the particle and the well
                float distanceSquared = sqr(particles[j].x - wells[i].x) + sqr(particles[j].y - wells[i].y);

                // Find the inverse distance between the particle and the well
                float invDistance = InvSqrt(distanceSquared);

                // Find the force affecting the particle
                float force = k * wells[i].charge * invDistance;

                if (force > k) force = k;
                if (force < -k) force = -k;

                // Factor in friction
                particles[j].vx *= friction;
                particles[j].vy *= friction;

                // Add the accelleration
                particles[j].vx += force * ((wells[i].x - particles[j].x) * invDistance);
                particles[j].vy += force * ((wells[i].y - particles[j].y) * invDistance);
            }
        }

        // Calculate how much force the meta forces are adding
        float forceX = 0, forceY = 0;
        for (i = 0; i < metaForces_length; ++i)
        {
            forceX += metaForces[i].vx;
            forceY += metaForces[i].vy;
        }

        // Move the particles
        for (i = 0; i < particles_length; ++i)
        {
            // Ignore the particle if its inactive
            if (particles[i].active == 0) continue;

            // Add the metaForces' force to the particle
            particles[i].vx += forceX;
            particles[i].vy += forceY;

            //if (particles[i].x < 0 || particles[i].x > zwidth || particles[i].y < 0 || particles[i].y > zheight) remParticle(i);
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;

            if (particles[i].x > zwidth)
            {
                particles[i].x = zwidth;
                particles[i].vx *= -1;
            }

            if (particles[i].x < 0)
            {
                particles[i].x = 0;
                particles[i].vx *= -1;
            }

            if (particles[i].y > zheight)
            {
                particles[i].y = zheight;
                particles[i].vy *= -1;
            }

            if (particles[i].y < 0)
            {
                particles[i].y = 0;
                particles[i].vy *= -1;
            }
        }
    }
}
