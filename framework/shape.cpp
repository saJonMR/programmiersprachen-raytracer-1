#include"shape.hpp"

Shape::Shape():
    name_{""},
    color_{0.f, 0.f, 0.f}{}


Shape::Shape(std::string name, Color c):
    name_{name},
    color_{c}{}

std::ostream& Shape::print(std::ostream& os)const{
    os<<std::endl<<"Name:"<<name_<<", Color:"<<color_;
    return os;
}

std::ostream& operator<<(std::ostream& os , Shape const& s){
    s.print(os);
    return os;
}
