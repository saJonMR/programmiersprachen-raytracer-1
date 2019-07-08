#include "box.hpp"

Box::Box():
    Shape(),
    min_{0.f, 0.f, 0.f},
    max_{0.f, 0.f, 0.f}{}

Box::Box(glm::vec3 min, glm::vec3 max):
    Shape(),
    min_{min},
    max_{max}{}


Box::Box(glm::vec3 min, glm::vec3 max, std::string const& name_, std::shared_ptr<Material> const& color_) :
    Shape(name_, color_),
    min_{min},
    max_{max}{}


float Box::area() const{
        float Area1 = sqrt(pow(min_.y-max_.y,2)) * sqrt(pow(min_.x-max_.x,2));
        float Area2 = sqrt(pow(min_.y-max_.y,2)) * sqrt(pow(min_.z-max_.z,2));
        return Area1*Area2;
    }


float Box::volume() const{
    float Volume = (max_.x-min_.x) * (max_.y-min_.y) * (max_.z-min_.z);
        return Volume;
}

std::ostream& Box::print(std::ostream& os)const{
    Shape::print(os);
    os<<"Minipunkt: "<<"X:"<<min_.x<<", Y:"<<min_.y<<", Z:"<<min_.z<<
    " Maxpunkt: "<<"X:"<<max_.x<<", Y:"<<max_.y<<", Z:"<<max_.z<<std::endl<<std::endl;
    return os;
}
HitPoint Box::intersect(Ray const& ray, float& t){
    float r = (min_.x - ray.origin.x)/ray.direction.x;
    bool test = false;
    float py = ray.origin.y + r * ray.direction.y;
    float pz = ray.origin.z + r * ray.direction.z;
    if(min_.y<=py && py<=max_.y){
        if(min_.z<=pz && pz<=max_.z){
            test=true;
        }
    }
    if(t<r){
        test= false;
    }
    HitPoint result{test, t, name_, color_, ray.origin, ray.direction};
    return result;
}