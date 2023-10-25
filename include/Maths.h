#pragma once

class Maths
{
public:
    template <typename T> static int sign(T val);
};

template <typename T>
inline int Maths::sign(T val)
{
    if (val < 0) return -1;
    else if (val > 0) return 1;
    else return 0;
}
