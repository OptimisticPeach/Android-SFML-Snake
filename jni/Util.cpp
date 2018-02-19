#include "Util.hpp"
#include <math.h>

float getAngle(sf::Vector2f a, sf::Vector2f b){
    return atan2f(((-a.y)+b.y),(a.x - b.x)) + 3.1415926535897932384626433832795f;
}

float toGradians(float radians)
{
    return radians; //(radians * 360) / (2 * 3.1415926535897923284626433832795f);
}

float dist(sf::Vector2f a, sf::Vector2f b)
{
    return sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}