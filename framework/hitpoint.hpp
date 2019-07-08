
#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include "color.hpp"
#include <iostream>
#include<glm/vec3.hpp>
#include <material.hpp>
#include <memory>
struct HitPoint{
    bool cut_ = false;
    float distance_ = 0.f;
    std::string name_;
    std::shared_ptr<Material> color_;
    glm::vec3 cutpoint_;
    glm::vec3 cutdirection_;
};

#endif