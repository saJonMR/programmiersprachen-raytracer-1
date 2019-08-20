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
    float dist = (bildwidth/2)/tan((S.camvec[0]->degree_/2))/180 * M_PI;
    glm::vec3 raydirection (bildwidth/2, bildheight/2, -dist);
    glm::vec3 origin (0.0, 0.0, 0.0);
    Ray Raymond {origin, raydirection};
    float raydist = 5000.f;
    Color c {0.f, 0.f, 0.f};
    for(int i = 0; i < S.shapevec.size(); i++) {
        if(S.shapevec[i]->intersect(Raymond, raydist).cut_){
            c = S.shapevec[i]->intersect(Raymond, raydist).color_->ka;
            std::cout<<"HIT"<<std::endl;
        }
        else{
            c = {0.f, 0.f, 0.f};
        } 
        return c;
    }
    
}
#endif