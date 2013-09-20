#include <math.h>
#include <stdlib.h>

float randInF(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * abs(min - max);
}

int randInI(int min, int max)
{
    return min + (rand() % abs(max - min));
}

unsigned int randInUI(unsigned int min, unsigned int max)
{
    return min + ((unsigned int)rand() % (max - min));
}

float InvSqrt (float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}
