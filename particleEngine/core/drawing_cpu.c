#include <assert.h>
#include "SDL/SDL.h"

#include "drawing.h"
#include "items.h"
#include "auxiliary/math+.h"

SDL_Surface* screen = NULL;

int drawSurface_width = 0;
int drawSurface_height = 0;

int draw_init(int zwidth, int zheight)
{
    assert(screen == NULL);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1) return -1;

    // Make sure that SDL_Quit is called if we exit
    atexit(SDL_Quit);

    // Get a drawing surface to play with
    screen = SDL_SetVideoMode(zwidth, zheight, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    // Let the rest of the program know the dimensions
    drawSurface_width = zwidth;
    drawSurface_height = zheight;

    SDL_WM_SetCaption("Particles - FPS: ?", "Particles");

    // Make sure it didn't fail (that'd suck)
    if (screen == NULL) return -1;

    return 0;
}

void draw_resize(int zwidth, int zheight)
{
    // Create a new screen
    screen = SDL_SetVideoMode(zwidth, zheight, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    // Let the rest of the program know about the chance
    drawSurface_width = zwidth;
    drawSurface_height = zheight;

    return;
}

/**
 * A helper function for drawSquare that blends two colors together with the
 * given alpha value.
 *
 * \param z1[in]          The first color
 * \param zaplhaMinus[in] 100 minus the alpha value
 * \param zr[in]          The red component of the second color multiplied by the alpha value
 * \param zg[in]          The green component of the second color multiplied by the alpha value
 * \param zb[in]          The blue component of the second color multiplied by the alpha value
 *
 * \return The resulting color.
 **/
inline color blend(color z1, unsigned int zalphaMinus, unsigned int zr, unsigned int zg, unsigned int zb)
{
    // Get the color components of z1
    colorComponent r, g, b;
    getRGB(z1, &r, &g, &b);

    // Return the result
    return rgb((r * zalphaMinus + zr) / 100,
               (g * zalphaMinus + zg) / 100,
               (b * zalphaMinus + zb) / 100);
}

/**
 * Draws an alpha blended solid color square on a given color array.
 *
 * \param zcolors[in,out]   The color array to draw to.
 * \param zcolor[in]        The color of the square
 * \param zalpha[in]        The alpha value of the square
 * \param zradius[in]       The radius of the square, or half its width or height minus 1. 0 signifies a single point.
 * \param zx[in]            The X coordinate of the center of the square on the color array.
 * \param zy[in]            The Y coordinate of the center of the square on the color array.
 * \param zscreenWidth[in]  The width of the color array.
 * \param zscreenHeight[in] The height of the color array.
 **/
void drawSquare(color* zcolors, color zcolor, int zalpha, int zradius, int zx, int zy, int zscreenWidth, int zscreenHeight)
{
    // Get the color components for zcolor
    colorComponent cr, cg, cb;
    getRGB(zcolor, &cr, &cg, &cb);

    // Convert the color component (byte) values to unsigned ints
    unsigned int r = (unsigned int)cr, g = (unsigned int)cg, b = (unsigned int)cb;

    // Do some calculations up front
    r *= zalpha; g *= zalpha; b *= zalpha;
    unsigned int alphaMinus = 100 - zalpha;

    // Get our adjusted initial coordinate values (clip anything off screen)
    unsigned int initialX, initialY;
    if (zradius > zx) initialX = 0; else initialX = zx - zradius;
    if (zradius > zy) initialY = 0; else initialY = zy - zradius;
    if (initialX > zscreenWidth - 1 || initialY > zscreenHeight - 1) return;

    // Get the starting point on the screen
    color* initial_rgb = zcolors + initialY * zscreenWidth + initialX;
    color* rgb = initial_rgb;

    // Get the width of the square
    unsigned int width = zradius * 2 + 1;

    // Get the adjusted width and height of the square
    unsigned int adjustedWidth = width, adjustedHeight = width;
    if (initialX + adjustedWidth > zscreenWidth - 1) adjustedWidth = zscreenWidth - initialX - 1;
    if (initialY + adjustedHeight > zscreenHeight - 1) adjustedHeight = zscreenHeight - initialY - 1;

    // Calculate the last possible rgb
    color* rgbMaxRow = initial_rgb + zscreenWidth * adjustedHeight + adjustedWidth;

    // Loop through each row
    while (rgb <= rgbMaxRow)
    {
        // Loop through each column in the row
        color* rgbMaxCol = rgb + adjustedWidth;
        do
            (*rgb) = blend(*rgb, alphaMinus, r, g, b);
        while (++rgb <= rgbMaxCol);

        // Retrive the color we'll be playing with
        initial_rgb += zscreenWidth;
        rgb = initial_rgb;
    }
}

int draw()
{
    const float expectedMaxSpeed = 2.0;

    // Clear the screen
    SDL_FillRect(screen, NULL, (color)0);

    // Lock the screen so we can do per-pixel calculations on it safely
    if (SDL_MUSTLOCK(screen) != 0) SDL_LockSurface(screen);

    // Get a pointer to the colors array
    color* colors = (color*)screen->pixels;

    // Draw the particles
    int i;
    for (i = 0; i < particles_length; ++i)
    {
        // Ignore the particle if its inactive.
        if (particles[i].active == 0) continue;

        int y = (int)(particles[i].y);
        int x = (int)(particles[i].x);
        if (y >= drawSurface_height || y < 0) continue;
        if (x >= drawSurface_width || x < 0) continue;

        float speed = 1 / InvSqrt(sqr(particles[i].vx) + sqr(particles[i].vy));
        int size = particles[i].radius_min + (int)((speed / expectedMaxSpeed) * particles[i].radius_max);
        if (size > particles[i].radius_min + particles[i].radius_max) size = particles[i].radius_min + particles[i].radius_max;

        drawSquare(colors, particles[i].color, particles[i].alpha, size, x, y, drawSurface_width, drawSurface_height);
    }

    // Unlock the surface
    if (SDL_MUSTLOCK(screen) != 0) SDL_UnlockSurface(screen);

    // Swap the buffers
    SDL_Flip(screen);

    return 0;
}
