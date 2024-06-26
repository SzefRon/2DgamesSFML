#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>

class Maths
{
public:
    template <typename T> static int sign(T val);
    template <typename T> static T min(T val1, T val2);
    template <typename T> static T max(T val1, T val2);
    template <typename T> static T clamp(T val, T min, T max);
    static float len(sf::Vector2f v);
    static int randInt(int min, int max);
    static float getAngleBetween(sf::Vector2f v1, sf::Vector2f v2);
    static float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
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

template <typename T>
inline T Maths::clamp(T val, T min, T max)
{
    return Maths::max(Maths::min(val, max), min);
}

inline float Maths::len(sf::Vector2f v)
{
    return std::sqrtf(v.x * v.x + v.y * v.y);
}

inline int Maths::randInt(int min, int max)
{
    return (rand() % (max - min) + min);
}

inline float Maths::getAngleBetween(sf::Vector2f v1, sf::Vector2f v2)
{
    return std::acosf((dotProduct(v1, v2)) / (len(v1) * len(v2)));
}

inline float Maths::dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
