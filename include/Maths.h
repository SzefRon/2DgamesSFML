#pragma once

#include <stdlib.h>

class Maths
{
public:
    template <typename T> static int sign(T val);
    template <typename T> static T min(T val1, T val2);
    template <typename T> static T max(T val1, T val2);
    static float randFloat(float from, float to)
    {
        return from + (rand() / (RAND_MAX / (to - from)) );
    }
};

template <typename T>
inline int Maths::sign(T val)
{
    if (val < 0) return -1;
    else if (val > 0) return 1;
    else return 0;
}

template <typename T>
inline T Maths::min(T val1, T val2)
{
    if (val1 < val2) return val1;
    return val2;
}

template <typename T>
inline T Maths::max(T val1, T val2)
{
    if (val1 > val2) return val1;
    return val2;
}
