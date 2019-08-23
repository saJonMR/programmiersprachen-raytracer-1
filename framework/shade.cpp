//
// Created by Jonas Roquette on 2019-08-23.
//

#ifndef SHADE_HPP
#define SHADE_HPP
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "hitpoint.hpp"
#include "shape.hpp"

Color shade(std::shared_ptr<Shape> Objekt, Ray r, float distance, Scene S){
    glm::vec3 hitpoint{r.direction.x * distance, r.direction.y * distance, r.direction.z * distance};
    glm::vec3 Sun = S.lichtvec[0]->position;
    Ray sunray{hitpoint, Sun};
    float raydis = 10000000.f;
    Color c {1.f, 1.f, 1.f};
    for(int i = 0; i < S.shapevec.size(); i++){
        if(S.shapevec[i]->intersect(sunray, raydis).cut_){
            std::cout<<"IMWEG"<<std::endl;
            return c;
        }
    }
    glm::vec3 normalenvektor = Objekt->givenormalvek(hitpoint);
    glm::vec3 lichtvektor{hitpoint.x - Sun.x, hitpoint.y - Sun.y, hitpoint.z - Sun.z};
    float incosoben = normalenvektor.x * lichtvektor.x + normalenvektor.y * lichtvektor.y + normalenvektor.z * lichtvektor.z;
    float incosuntennorm = sqrt(normalenvektor.x * normalenvektor.x + normalenvektor.y * normalenvektor.y + normalenvektor.z * normalenvektor.z);
    float incosuntenlicht = sqrt(lichtvektor.x * lichtvektor.x + lichtvektor.y * lichtvektor.y + lichtvektor.z * lichtvektor.z);

    float Intens = S.lichtvec[0]->brightness * cosf(incosoben/(incosuntenlicht*incosuntennorm));
    float ROT = (Objekt->color_->kd.r + S.lichtvec[0]->color.r) * Intens;
    float GRUN = (Objekt->color_->kd.g + S.lichtvec[0]->color.g) * Intens;
    float BLAU = (Objekt->color_->kd.b + S.lichtvec[0]->color.b) * Intens;
    c = {ROT, GRUN, BLAU};
    return c;
}
#endif
