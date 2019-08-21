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
    bool test = false;
    float t_x = (min_.x - ray.origin.x)/ray.direction.x;        //min x Ebene Sp
    float p1y = ray.origin.y + t_x * ray.direction.y;
    float p1z = ray.origin.z + t_x * ray.direction.z;

    float t_y = (min_.y - ray.origin.y)/ray.direction.y;        //min y Ebene Sp
    float p2x = ray.origin.x + t_y * ray.direction.x;
    float p2z = ray.origin.z + t_y * ray.direction.z;

    float t_z = (min_.z - ray.origin.z)/ray.direction.z;        //min z Ebene Sp
    float p3x = ray.origin.x + t_z * ray.direction.x;
    float p3y = ray.origin.y + t_z * ray.direction.y;


    


    float r_x = (max_.x - ray.origin.x)/ray.direction.x;        //max x Ebene Sp
    float p4y = ray.origin.y + r_x * ray.direction.y;
    float p4z = ray.origin.z + r_x * ray.direction.z;

    float r_y = (max_.y - ray.origin.y)/ray.direction.y;        //max y Ebene Sp
    float p5x = ray.origin.x + r_y * ray.direction.x;
    float p5z = ray.origin.z + r_y * ray.direction.z;

    float r_z = (max_.z - ray.origin.z)/ray.direction.z;        //max y Ebene Sp
    float p6x = ray.origin.x + r_z * ray.direction.x;
    float p6y = ray.origin.y + r_z * ray.direction.y;
    glm::vec3 Links, Rechts, Oben, Unten, Vorne, Hinten;

    // Teste der min x, y, z Ebenen
    if(min_.y<=p1y && p1y<=max_.y){
        if(min_.z <= p1z && p1z<=max_.z){
            test=true;
            Links={min_.x, p1y, p1z};
        }
    }
    if(min_.x <= p2x && p2x<=max_.x){
        if(min_.z<=p2z && p2z<=max_.z){
            test=true;
            Unten={p2x, min_.y, p2z};
        }
    }
    if(min_.x <= p3x && p3x<=max_.x){     //Vorne
        if(min_.y<=p3y && p3y<=max_.y){
            test=true;
            Vorne={p3x, p3y, min_.z};
        }
    }

    //Teste der max x, y, z Ebenen
    if(min_.y <= p4y && p4y<=max_.y){
        if(min_.z<=p4z && p4z<=max_.z){
            test=true;
            Rechts={max_.x, p4y, p4z};
        }
    }
    if(min_.x <= p5x&& p5x<=max_.x){
        if(min_.z<=p5z && p5z<=max_.z){
            test=true;
            Oben={p5x, max_.y, p5z};
        }
    }
    if(min_.x <= p6x && p6x<=max_.x){
        if(min_.y<=p6y && p6y<=max_.y){
            test=true;
            Hinten={p6x, p6y, max_.z};
        }
    }
    float distanceL = sqrtf(fabsf(ray.origin.x - Links.x)*fabsf(ray.origin.x - Links.x)+ fabsf(ray.origin.y - Links.y)*fabsf(ray.origin.y - Links.y) + fabsf(ray.origin.z - Links.z)*fabsf(ray.origin.z - Links.z));
    float distanceR = sqrtf(fabsf(ray.origin.x - Rechts.x)*fabsf(ray.origin.x - Rechts.x)+ fabsf(ray.origin.y - Rechts.y)*fabsf(ray.origin.y - Rechts.y) + fabsf(ray.origin.z - Rechts.z)*fabsf(ray.origin.z - Rechts.z));
    float distanceO = sqrtf(fabsf(ray.origin.x - Oben.x)*fabsf(ray.origin.x - Oben.x)+ fabsf(ray.origin.y - Oben.y)*fabsf(ray.origin.y - Oben.y) + fabsf(ray.origin.z - Oben.z)*fabsf(ray.origin.z - Oben.z));
    float distanceU = sqrtf(fabsf(ray.origin.x - Unten.x)*fabsf(ray.origin.x - Unten.x)+ fabsf(ray.origin.y - Unten.y)*fabsf(ray.origin.y - Unten.y) + fabsf(ray.origin.z - Unten.z)*fabsf(ray.origin.z - Unten.z));
    float distanceV = sqrtf(fabsf(ray.origin.x - Vorne.x)*fabsf(ray.origin.x - Vorne.x)+ fabsf(ray.origin.y - Vorne.y)*fabsf(ray.origin.y - Vorne.y) + fabsf(ray.origin.z - Vorne.z)*fabsf(ray.origin.z - Vorne.z));
    float distanceH = sqrtf(fabsf(ray.origin.x - Hinten.x)*fabsf(ray.origin.x - Hinten.x)+ fabsf(ray.origin.y - Hinten.y)*fabsf(ray.origin.y - Hinten.y) + fabsf(ray.origin.z - Hinten.z)*fabsf(ray.origin.z - Hinten.z));
    float finaldistance = 100000000.f;
    std::vector<float> distances{distanceL, distanceR, distanceO, distanceU, distanceV, distanceH};
    for(int i = 0; i<distances.size(); i++){
        if(distances[i]!=0.f){
            if(distances[i] < finaldistance){
                 finaldistance = distances[i];
            }
        }
    }
    HitPoint result{test, finaldistance, name_, color_, ray.origin, ray.direction};
    return result;
}