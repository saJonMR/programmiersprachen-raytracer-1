#ifndef BOX_HPP
#define BOX_HPP
#include<glm/vec3.hpp>
#include"shape.hpp"
#include<catch.hpp>
#include<ray.hpp>
#include<hitpoint.hpp>
class Box : public Shape{
    private:
    glm::vec3 min_;
    glm::vec3 max_;
    public:
    Box();
    Box(glm::vec3 min, glm::vec3 max);
    Box(glm::vec3 min, glm::vec3 max, std::string const& name_, Color const& color_);
    //Box(std::string const& name_, glm::vec3 min, glm::vec3 max);
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os)const override;
    bool intersect(Ray const& ray, float& t)override;
    ~Box()override{std::cout<<std::endl<<"BOX DEKUNSTRUKTOR VON: "<<name_<<std::endl;}
};
#endif