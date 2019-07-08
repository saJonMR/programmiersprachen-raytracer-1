#include "sphere.hpp"
#include "hitpoint.hpp"
#include <glm/gtx/intersect.hpp>
Sphere::Sphere():
    Shape(),
    mp_{0.f, 0.f, 0.f},
    radius_{0.f}{}

Sphere::Sphere(glm::vec3 mp, float r):
    Shape(),
    mp_{mp},
    radius_{r}{}

Sphere::Sphere(glm::vec3 mp, float r, std::string const& name_, Color const& c):
    Shape(name_, color_),
    mp_{mp},
    radius_{r}{}


float Sphere::area() const{
    float result = 4*M_PI*radius_*radius_;
    return result;
}

float Sphere::volume() const{
    float result = 4.0/3.0*M_PI*radius_*radius_*radius_;
    return result; 
}

std::ostream& Sphere::print(std::ostream& os)const{
    Shape::print(os);
    os<<"Mittelpunkt: "<<"X:"<<mp_.x<<", Y:"<<mp_.y<<", Z:"<<mp_.z<<
    ", Radius:"<<radius_<<std::endl<<std::endl;
    return os;
}

bool Sphere::intersect(Ray const& ray, float& t){
    bool test;
    test=glm::intersectRaySphere(ray.origin,glm::normalize(ray.direction),mp_,radius_*radius_,t);
    HitPoint result{test, t, name_, color_, ray.origin, ray.direction};
    return test;
}