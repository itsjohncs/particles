#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include "particleEngine/core/core.h"

static const WINDOW_WIDTH = 700;
static const WINDOW_HEIGHT = 500;

// The number of "steps" (the smallest unit of time in the simulation) that
// should occur every second.
static const int STEPS_PER_SECOND = 100;

static int mouseWell = -1;
void setupDemo()
{
    int newGenerator = addGenerator();
    generators[newGenerator].x = 100.0;
    generators[newGenerator].y = 100.0;
    generators[newGenerator].vx = 0.5;
    generators[newGenerator].vy = 0.0;
    generators[newGenerator].countdown_max = 5;
    generators[newGenerator].radius = 20;

    newGenerator = addGenerator();
    generators[newGenerator].x = 900.0;
    generators[newGenerator].y = 100.0;
    generators[newGenerator].vx = 0.0;
    generators[newGenerator].vy = 0.5;
    generators[newGenerator].countdown_max = 5;
    generators[newGenerator].radius = 20;

    newGenerator = addGenerator();
    generators[newGenerator].x = 900.0;
    generators[newGenerator].y = 600.0;
    generators[newGenerator].vx = -0.5;
    generators[newGenerator].vy = 0.0;
    generators[newGenerator].countdown_max = 5;
    generators[newGenerator].radius = 20;

    newGenerator = addGenerator();
    generators[newGenerator].x = 100.0;
    generators[newGenerator].y = 600.0;
    generators[newGenerator].vx = 0.0;
    generators[newGenerator].vy = -0.5;
    generators[newGenerator].countdown_max = 5;
    generators[newGenerator].radius = 20;

    int newMetaForce = addMetaForce();
    metaForces[newMetaForce].vx = 0.0;
    metaForces[newMetaForce].vy = 0.005;

    mouseWell = addWell();
    wells[mouseWell].x = 0;
    wells[mouseWell].y = 0;
    wells[mouseWell].charge = 50.0;
}

int main(int argc, char *argv[])
{
    // Create a bunch of generators and well that we can use to test everything out
    setupDemo();

    // Set up the randomizer
    srand(time(NULL));

    clock_t t = clock();
    int ticks = 0;

    clock_t t2 = clock();
    int timeElapsed = 0;

    if (draw_init(WINDOW_WIDTH, WINDOW_HEIGHT) != 0) exit(-1);

    int running = 1;
    while (running == 1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) == 1)
        {
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                    wells[mouseWell].x = event.motion.x;
                    wells[mouseWell].y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    wells[mouseWell].charge = -500.0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    wells[mouseWell].charge = 50.0;
                    break;
                case SDL_VIDEORESIZE:
                    draw_resize(event.resize.w, event.resize.h);
                    break;
                case SDL_KEYDOWN:
                    particles_cap += 50;
                    break;
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }

        int c = clock();
        timeElapsed += c - t2;
        t2 = c;
        if (timeElapsed >= CLOCKS_PER_SEC / STEPS_PER_SECOND)
        {
            step(drawSurface_width, drawSurface_height, timeElapsed / (CLOCKS_PER_SEC / STEPS_PER_SECOND));
            timeElapsed -= timeElapsed - timeElapsed % (CLOCKS_PER_SEC / STEPS_PER_SECOND);
            draw();
            ++ticks;
        }

        if (ticks == 1000)
        {
            clock_t t_now = clock();
            SDL_WM_SetCaption("Particles - FPS: ?", "Particles");
            char s[100];
            sprintf((char*)&s, "Particles - FPS: %f", 1.0 / (((t_now - t) / (float)CLOCKS_PER_SEC) / 1000.0));
            SDL_WM_SetCaption((char*)&s, "Particles");
            // printf("Time Elapsed: %f seconds (%f fps)\n", (t_now - t) / (float)CLOCKS_PER_SEC, 1.0 / (((t_now - t) / (float)CLOCKS_PER_SEC) / 1000.0));
            t = t_now;
            ticks = 0;
        }
    }

    free(wells);
    free(particles);
    free(generators);

    return 0;
}
