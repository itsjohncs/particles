#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

#include "SDL/SDL.h"

/**
 * When specifying a color, use the \e rgb function.
 **/
typedef Uint32 color;

/**
 * A single component of a color (red, gree, blue, or alpha).
 **/
typedef Uint8 colorComponent;

/**
 * Creates a color from its components.
 *
 * \param r[in] The red component of the color.
 * \param g[in] The green component of the color.
 * \param b[in] The blue component of the color.
 *
 * \return The color specified.
 **/
static inline color rgb(colorComponent r, colorComponent g, colorComponent b)
{
    // Get access to the screen variable
    extern SDL_Surface* screen;

    // Map the RGB values to the correct format and return
    return SDL_MapRGB(screen->format, r, g, b);
}

/**
 * Gets the components of a color
 *
 * \param zcolor[in] The color were getting the components of.
 * \param r[out]     The red component of the color.
 * \param g[out]     The green component of the color.
 * \param b[out]     The blue component of the color.
 **/
static inline void getRGB(color zcolor, colorComponent* r, colorComponent* g, colorComponent* b)
{
    // Get access to the screen variable
    extern SDL_Surface* screen;

    // Get the rgb components
    SDL_GetRGB(zcolor, screen->format, r, g, b);
}

/**
 * Draws the screen onto the sepcified device context.
 *
 * \param ztargetDC[in] The device context to draw onto.
 * \param zarea[in]     The bounds in which to draw the screen on the dc.
 *
 * \return Returns 0
 **/
int draw();

int draw_init(int zwidth, int zheight);

void draw_resize(int zwidth, int zheight);

extern int drawSurface_width;

extern int drawSurface_height;

#endif // DRAWING_H_INCLUDED
