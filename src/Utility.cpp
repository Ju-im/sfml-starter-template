#include "Utility.h"


Utility::Utility()
{
  
}

Utility::~Utility()
{
    

}







sf::Vector2f Utility::rotateVec(sf::Vector2f& newNormal, float deg)
{
    float r = deg * 3.14159265f / 180.f;

    float c = std::cos(r);
    float s = std::sin(r);

    return { newNormal.x * c - newNormal.y * s,
             newNormal.x * s + newNormal.y * c };
}





float Utility::radToDeg(float rad)
{
    return rad * 180.f / 3.14159265f;
}

float Utility::degToRad(float deg)
{
    return deg * 3.14159265f / 180.f;
}


float Utility::lerp(float v1, float v2, float t)
{
    return v1 + t * (v2 - v1);
}


float Utility::PerlinNoise1D(float x)
{ // grid points around x
    int left = static_cast<int>(std::floor(x));
    int right = left + 1;

    float d1 = x - left;
    float d2 = x - right; // finding the distance

    float grad1 = gradient(left);  // -1 or +1
    float grad2 = gradient(right); // -1 or +1

    float v1 = grad1 * d1;
    float v2 = grad2 * d2;
    float t = fade(d1);

    return lerp(v1, v2, t);
}
float Utility::gradient(int x)
{
    int h = hash1D(x);
    return (h & 1) == 0 ? 1.0f : -1.0f;
}
int Utility::hash1D(int x)
{
    x = (x ^ 61) ^ (x >> 16);
    x *= 9;
    x = x ^ (x >> 4);
    x *= 0x27d4eb2d;
    x = x ^ (x >> 15);
    return x;
}

float Utility::fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}