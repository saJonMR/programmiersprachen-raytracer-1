#ifndef SPHERE_HPP
#define SPHERE_HPP
#include<glm/vec3.hpp>
#include"shape.hpp"
#include<catch.hpp>
#include<ray.hpp>
#include<hitpoint.hpp>
class Sphere : public Shape{
    private:
    glm::vec3 mp_;
    float radius_;
    public:
    Sphere();
    Sphere(glm::vec3 mp, float r);
    Sphere(glm::vec3 mp, float r, std::string const& name_, Color const& color_);
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os)const override;
    bool intersect(Ray const& ray, float& t)override;
    ~Sphere()override{std::cout<<std::endl<<"SPHERE DEKUNSTRUKTOR VON: "<<name_<<std::endl;}

};

#endif