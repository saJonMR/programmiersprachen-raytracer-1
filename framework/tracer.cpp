#ifndef TRACER_HPP
#define TRACER_HPP
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "hitpoint.hpp"

Color tracer(Scene S, int x, int y, int bildwidth, int bildheight){
    int my_x = x/bildwidth * S.res_x;
    int my_y = y/bildheight * S.res_y;
    float dist = (S.res_x/2)/tan(S.camvec[0]->degree_/2);
    glm::vec3 raydirection (my_x-S.res_x/2, my_y-S.res_y/2, -dist);
    glm::vec3 origin (0.0, 0.0, 0.0);
    Ray Raymond {origin, raydirection};
    float raydist = 5000.f;
    Color c;
    if(S.shapevec[1]->intersect(Raymond, raydist).cut_){
        c = S.shapevec[1]->intersect(Raymond, raydist).color_->ka;
        std::cout<<"HIT"<<std::endl;
    }
    else{
        c = {0.f, 0.f, 0.f};
    } 
    return c;
}
#endif