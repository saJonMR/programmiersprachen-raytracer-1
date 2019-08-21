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
    float dist = ((bildwidth/2)/tan(S.camvec[0]->degree_/2))/180 * M_PI;
    glm::vec3 raydirection (x-bildwidth/2, y-bildheight/2, -dist);
    glm::vec3 origin (0.0, 0.0, 0.0);
    Ray Raymond {origin, raydirection};
    float raydist = 5000.f;
    Color c {0.f, 0.f, 0.f};
    float mindistance = 10000;
    std::shared_ptr<Shape> circle = S.shapevec[1];
    std::shared_ptr<Shape> box = S.shapevec[0];
    
    if(circle->intersect(Raymond, raydist).cut_){
        if(box->intersect(Raymond, raydist).cut_){
            if(circle->intersect(Raymond, raydist).distance_< box->intersect(Raymond, raydist).distance_){
                c = circle->intersect(Raymond, raydist).color_->ka;  
            }
        }
        else{
            c = circle->intersect(Raymond, raydist).color_->ka;
        }
    }
    if(box->intersect(Raymond, raydist).cut_){
        if(circle->intersect(Raymond, raydist).cut_){
            if(box->intersect(Raymond, raydist).distance_< circle->intersect(Raymond, raydist).distance_){
                c = box->intersect(Raymond, raydist).color_->ka;
            }
        }
        else{
            c = box->intersect(Raymond, raydist).color_->ka;
        }
    }
    
    return c;
}
#endif