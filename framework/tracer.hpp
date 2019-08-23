#ifndef TRACER_HPP
#define TRACER_HPP
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "hitpoint.hpp"
#include "shade.hpp"
Color tracer(Scene S, int x, int y, int bildwidth, int bildheight){
    float dist = ((bildwidth/2)/tan(S.camvec[0]->degree_/2))/180 * M_PI;
    glm::vec3 raydirection (x-bildwidth/2, y-bildheight/2, -dist);
    glm::vec3 origin (0.0, 0.0, 0.0);
    Ray Raymond {origin, raydirection};
    float raydist = 5000.f;
    Color c {0.f, 0.f, 0.f};
    float mindistance = 10000;
    for(int i = 0; i < S.shapevec.size(); i++){
        if(S.shapevec[i]->intersect(Raymond, raydist).cut_){
            for(int j = 0; j < S.shapevec.size(); j++){
                if(S.shapevec[j]!=S.shapevec[i]){
                    if(S.shapevec[j]->intersect(Raymond, raydist).cut_){
                        if(S.shapevec[i]->intersect(Raymond, raydist).distance_ < S.shapevec[j]->intersect(Raymond, raydist).distance_){
                            c = S.shapevec[i]->intersect(Raymond, raydist).color_->ka;
                            if(S.shapevec[i]->name_ == "rtoppom"){
                                std::cout<<"HERETICBURN!!"<<std::endl;
                            }
                        }
                        else{
                            c = S.shapevec[j]->intersect(Raymond, raydist).color_->ka;
                            break;
                        }
                    }
                }
                if(j+1 == S.shapevec.size()){
                    c = S.shapevec[i]->intersect(Raymond, raydist).color_->ka;
                }
            }
        }
    }

    return c;
}
#endif