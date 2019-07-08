#include "color.hpp"
#include <iostream>
#include<glm/vec3.hpp>
#ifndef HITPOINT_HPP
#define HITPOINT_HPP

struct HitPoint{
    bool cut_ = false;
    float distance_ = 0.f;
    std::string name_;
    Color color_;
    glm::vec3 cutpoint_;
    glm::vec3 cutdirection_;
};
#endif