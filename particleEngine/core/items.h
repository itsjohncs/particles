#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include "drawing.h"

/// A structure defining a single particle in the system
typedef struct
{
    int active; /// < Whether the structure is in use or not (1 for yes, 0 for no).
    float x; /// < The x cordinate of the particle
    float y; /// < The y cordinate of the particle
    float vx; /// < The x velocity of the particle
    float vy; /// < The y velocity of the particle
    int radius_min; /// < The radius of the particle when it is at a complete standstill
    int radius_max; /// < The largest radius the particle will reach
    int alpha; /// < A value between 0 and 100 representing the alpha component of the particle's color
    color color; /// < The color of the particle
} particle;

/// A structure defining a single gravity well in the system
typedef struct
{
    float x; /// < The x cordinate of the well
    float y; /// < The y cordinate of the well
    float charge; /// < The well's charge (or mass)
} well;

/// A structure defining a single generator in the system
typedef struct
{
    float x; /// < The x cordinate of the generator in hundreths
    float y; /// < The y cordinate of the generator in hundreths
    float vx; /// < The initial x velocity given to a generated particle
    float vy; /// < The initial y velocity given to a generated particle.
    int radius; /// < The distance from the generator (approxamitly) that a particle can be generated
    int countdown; /// < The number of steps until the generator generates another particle
    int countdown_max; /// < The number of steps it takes for a generator to "reload" and create another particle
} generator;

/// A structure defining a single meta force in the system (massless disembodied forces that affect every particle equally independent of distance).
typedef struct
{
    float vx; /// < The x component of the meta force's force
    float vy; /// < The y component of the meta force's force
} metaForce;

extern particle* particles;   /// < An array of all the particles in the system
extern int particles_length;  /// < The length of the array (ignoring any unused allocated memory at the end)
extern int particles_size;    /// < The number of items the array can contain, including any unused allocated memory at the end.
extern int particles_num;     /// < The actual number of particles on screen
extern int particles_cap;     /// < The number of particlees allowed on screen.

extern well* wells;           /// < An array of all the gravity wells in the system
extern int wells_length;      /// < The length of the array (ignoring any unused allocated memory at the end)
extern int wells_size;        /// < The number of items the array can contain, including any unused allocated memory at the end.
extern int wells_num;         /// < The actual number of wells on screen

extern generator* generators; /// < An array of all the generators in the system
extern int generators_length; /// < The length of the array (ignoring any unused allocated memory at the end)
extern int generators_size;   /// < The number of items the array can contain, including any unused allocated memory at the end
extern int generators_num;    /// < The actual number of generators on screen

extern metaForce* metaForces; /// < An array of all the meta forces in the system
extern int metaForces_length; /// < The length of the array (ignoring any unused allocated memory at the end)
extern int metaForces_size;   /// < The number of items the array can contain, including any unused allocated memory at the end
extern int metaForces_num;    /// < The actual number of generators on screen

/**
 * Creates a new particle.
 *
 * \return Returns the index of the particle in the particles array.
 **/
int addParticle();

/**
 * Destroys a particle.
 *
 * \param zindex[in] The index of the particle to be destroyed.
 **/
void remParticle(int zindex);

/**
 * Creates a new well.
 *
 * \return Returns the index of the well in the wells array.
 **/
int addWell();

/**
 * Destroys a well.
 *
 * \param zindex[in] The index of the well to be destroyed.
 **/
void remWell(int zindex);

/**
 * Creates a new generator.
 *
 * \return Returns the index of the well in the generators array.
 **/
int addGenerator();

/**
 * Destroys a generator.
 *
 * \param zindex[in] The index of the generator to be destroyed.
 **/
void remGenerator(int zindex);

/**
 * Creates a new meta force.
 *
 * \return Returns the index of the meta force in the metaForces array.
 **/
int addMetaForce();

/**
 * Destroys a meta force.
 *
 * \param zindex[in] The index of the meta force to be destroyed.
 **/
void remMetaForce(int zindex);

#endif // ITEMS_H_INCLUDED
