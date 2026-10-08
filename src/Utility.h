#pragma once
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
class Utility
{
public:
    Utility();
    ~Utility();
   

   
    static sf::Vector2f rotateVec(sf::Vector2f& v, float deg);
    static char
        overlap(const sf::FloatRect& sprite1, const sf::FloatRect& sprite2);
    static sf::Vector2f
        push(const sf::FloatRect& sprite1, const sf::FloatRect& sprite2);
    static bool SAT(sf::Sprite& sprite1, sf::Sprite& sprite2);
    static float lerp(float v1, float v2, float t);

    static float radToDeg(float rad);
    static float degToRad(float deg);
    static float PerlinNoise1D(float x);
    static float gradient(int x);
    static int hash1D(int x);
    static float fade(float t);
    std::string tag;
    int layer = 0; // 1 is ground, 2 is player, 3 is enemy, 4 is projectiles, 5 is
    // UI


 
};

#endif // SFML_GAME_H
