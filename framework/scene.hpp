#include<glm/vec3.hpp>
#ifndef SCENE_HPP
#define SCENE_HPP
#include "color.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <material.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include <fstream>
#include <material.hpp>
#include <camera.hpp>
#include "lichtquelle.hpp"
struct Scene{
    public:
    std::vector<std::shared_ptr<Material>> materialvec;
    std::vector<std::shared_ptr<Sphere>> spherevec;
    std::vector<std::shared_ptr<Box>> boxvec;
    std::vector<std::shared_ptr<Camera>> camvec;
    std::vector<std::shared_ptr<Lichtquelle>> lichtvec;
    int res_x, res_y;
    std::shared_ptr<Material> findmat(std::string name_);
    Sphere makesphere(float number);
    Box makebox(float number);
    
};
Scene createscene(std::string path_string);



#endif