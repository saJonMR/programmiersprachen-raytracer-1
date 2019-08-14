#ifndef LICHTQUELLE_HPP
#define LICHTQUELLE_HPP
#include<glm/vec3.hpp>
#include "color.hpp"
#include <iostream>
#include "ray.hpp"
struct Lichtquelle{
    std::string name;
    glm::vec3 position;
    Color color;
    float brightness;
};
#endif