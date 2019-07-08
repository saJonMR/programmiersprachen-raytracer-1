#include<glm/vec3.hpp>
#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <iostream>

struct Material{
    std::string name = "Unnamed";
    Color ka{0.f, 0.f, 0.f};
    Color ks{0.f, 0.f, 0.f};
    Color kd{0.f, 0.f, 0.f};
    float m = 2;
    friend std::ostream& operator <<(std::ostream& os,Material const& c){
        os<<"Material Name: "<<c.name<<"\n"<<"Material KA: "<<c.ka<<"Material KD: "<<c.kd<<"Material KS: "<<c.ks<<"Material M: "<<c.m;
        return os;
    }
};

#endif