#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <iostream>
#include<hitpoint.hpp>
#include<ray.hpp>

class Shape{
    public:
    Shape();
    virtual float area()const=0;
    virtual float volume()const=0;
    virtual std::ostream& print(std::ostream& os)const;
    Shape(std::string name, Color c);
    virtual ~Shape(){std::cout<<std::endl<<"SHAPE DEKUNSTRUKTOR VON: "<<name_<<std::endl;}
    virtual bool intersect(Ray const& ray, float& t)=0;
    protected:
    std::string name_;
    Color color_;
};

std::ostream& operator<<(std::ostream& os , Shape const& s);

#endif