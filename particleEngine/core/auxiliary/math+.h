#ifndef MATHPLUS_H_INCLUDED
#define MATHPLUS_H_INCLUDED

#ifndef sqr
/// Calulates the square of a given number
#define sqr(q) ((q) * (q))
#endif

/**
 * Returns a random floating number between two numbers. This function does not reseed
 * the random generator. Ensure that \e srand is called at some point prior to this
 * function's execution.
 *
 * \param min[in] The lower bound of the range the generated number must fall within.
 * \param max[in] The upper bound of the range the generated number must fall within.
 *
 * \return A random number between min and max.
 **/
float randInF(float min, float max);

/**
 * Returns a random floating number between two numbers. This function does not reseed
 * the random generator. Ensure that \e srand is called at some point prior to this
 * function's execution.
 *
 * \param min[in] The lower bound of the range the generated number must fall within.
 * \param max[in] The upper bound of the range the generated number must fall within.
 *
 * \return A random number between min and max.
 **/
int randInI(int min, int max);

/**
 * Returns a random floating number between two numbers. This function does not reseed
 * the random generator. Ensure that \e srand is called at some point prior to this
 * function's execution.
 *
 * \param min[in] The lower bound of the range the generated number must fall within.
 * \param max[in] The upper bound of the range the generated number must fall within.
 *
 * \return A random number between min and max.
 **/
unsigned int randInUI(unsigned int min, unsigned int max);

/**
 * Returns the inverse square root of a floating point value, equivalent to
 * <tt>1 / sqrt(x)</tt>, however, this function is really really really fast.
 *
 * \note This function was in no way developed, modified, or fully comprehended
 *       by me. Credit goes to the original producer of this function, though I
 *       am not sure who that is. Fabled to be originally found in the Quake 3
 *       source code, this little gem is quite an amazing function.
 *
 * \param x[in] The number that the function will calculate the inverse square
 *              root of.
 *
 * \return The inverse square root of \e x.
 **/

float InvSqrt (float x);

#endif // MATHPLUS_H_INCLUDED
