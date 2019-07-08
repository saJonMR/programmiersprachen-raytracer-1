#include"shape.hpp"

Shape::Shape():
    name_{""},
    color_{std::make_shared<Material>(Material{}) }{}


Shape::Shape(std::string name, std::shared_ptr<Material> c):
    name_{name},
    color_{c}{}

std::ostream& Shape::print(std::ostream& os)const{
    os<<std::endl<<"Name: "<<name_<<"\n"<< "Material: "<<"\n"<< *color_<<"\n";
    return os;
}

std::ostream& operator<<(std::ostream& os , Shape const& s){
    s.print(os);
    return os;
}
