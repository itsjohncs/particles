#ifndef STEP_H_INCLUDED
#define STEP_H_INCLUDED

/**
 * Has the particle engine take one step forward in time.
 *
 * \param zwidth[in]  The width of the play area.
 * \param zheight[in] The height of the play area.
 **/
void step(int zwidth, int zheight, int ztime);

extern float friction; /// < Every particle's velocity will be multiplied by this value every step.

#endif // STEP_H_INCLUDED
