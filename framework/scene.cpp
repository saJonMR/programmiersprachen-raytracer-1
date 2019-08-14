#include "scene.hpp"

std::shared_ptr<Material> Scene::findmat(std::string name_){
    Material search_mat{};
    search_mat.name = name_;
    std::shared_ptr<Material> searchpointer = std::make_shared<Material>(search_mat);
    for(int i = 0;i<materialvec.size();i++){
        std::shared_ptr<Material> ogpointer = materialvec[i];
        if(searchpointer->name == ogpointer->name){
            std::cout<<std::endl<<ogpointer->name<<" GEFUNDEN"<<std::endl;
            return ogpointer;
        }
    }
    return nullptr;
}

Sphere Scene::makesphere(float number){
    
    std::shared_ptr<Sphere> my_pointer = spherevec[number];
    Sphere result {my_pointer->mp_,my_pointer->radius_,my_pointer->name_, my_pointer->color_ };
    return result;
}

Box Scene::makebox(float number){
    std::shared_ptr<Box> my_pointer = boxvec[number];
    Box result {my_pointer->min_, my_pointer->max_, my_pointer->name_, my_pointer->color_};
    return result;
}


Scene createscene(std::string path_string) {
    std::vector<std::shared_ptr<Material>> material_vec;
    std::vector<std::shared_ptr<Sphere>> sphere_vec;
    std::vector<std::shared_ptr<Box>> box_vec;
    std::vector<std::shared_ptr<Camera>> cam_vec;
    std::vector<std::shared_ptr<Lichtquelle>> licht_vec;
    Scene my_Scene{};
    std::string line_buffer;
    std::ifstream in_scene_file(path_string);

    while(std::getline(in_scene_file, line_buffer) ) {
        std::istringstream line_string_stream(line_buffer);
        std::string identifier;
        line_string_stream >> identifier;
        if("define" == identifier) {
            line_string_stream >> identifier;

            if("material" == identifier) {
                std::string material_name;
                line_string_stream >> material_name;
                float ka_red, ka_green, ka_blue;
                line_string_stream >> ka_red;
                line_string_stream >> ka_green;
                line_string_stream >> ka_blue;
                Color c1{ka_red, ka_green, ka_blue};

                line_string_stream >> ka_red;
                line_string_stream >> ka_green;
                line_string_stream >> ka_blue;
                Color c2{ka_red, ka_green, ka_blue};

                line_string_stream >> ka_red;
                line_string_stream >> ka_green;
                line_string_stream >> ka_blue;
                Color c3{ka_red, ka_green, ka_blue};

                float m;
                line_string_stream >>m;
                std::cout<<"Farbe: "<<material_name<<std::endl<<c1<<c2<<c3<<std::endl;
                std::shared_ptr<Material> pointer_material = std::make_shared<Material>(Material {material_name, c1, c2, c3, m});
                material_vec.push_back(pointer_material);
                my_Scene.materialvec = material_vec;
            }

            if("shape" == identifier){
                line_string_stream >> identifier;

                if("sphere" == identifier){
                    std::string sphere_name;
                    std::string material_name;
                    float vec_x, vec_y, vec_z, sphere_radius;
                    std::shared_ptr<Material> sphere_mat;

                    line_string_stream >> sphere_name;
                    line_string_stream >> vec_x;
                    line_string_stream >> vec_y;
                    line_string_stream >> vec_z;
                    line_string_stream >> sphere_radius;
                    line_string_stream >> material_name;

                    sphere_mat = my_Scene.findmat(material_name);
                    glm::vec3 mp{vec_x, vec_y, vec_z};
                    std::shared_ptr<Sphere> pointer_sphere = std::make_shared<Sphere>(Sphere{mp, sphere_radius, sphere_name, sphere_mat});
                    sphere_vec.push_back(pointer_sphere);
                    my_Scene.spherevec = sphere_vec;

                }
                
                if("box" == identifier){
                    std::string box_name;
                    std::string material_name;
                    float min_x, min_y, min_z, max_x, max_y, max_z;
                    std::shared_ptr<Material> box_mat;

                    line_string_stream >> box_name;
                    line_string_stream >> min_x;
                    line_string_stream >> min_y;
                    line_string_stream >> min_z;
                    line_string_stream >> max_x;
                    line_string_stream >> max_y;
                    line_string_stream >> max_z;
                    line_string_stream >> material_name;

                    box_mat = my_Scene.findmat(material_name);
                    glm::vec3 p1{min_x, min_y, min_z};
                    glm::vec3 p2{max_x, max_y, max_z};
                    std::shared_ptr<Box> pointer_box = std::make_shared<Box>(Box{p1, p2, box_name, box_mat});
                    box_vec.push_back(pointer_box);
                    my_Scene.boxvec = box_vec;
                }
            }
            if("light" == identifier){
                std::string licht_name;
                float pos_x, pos_y, pos_z, c_red, c_green, c_blue, brightness;
                
                line_string_stream >> licht_name;
                line_string_stream >>pos_x;
                line_string_stream >>pos_y;
                line_string_stream >>pos_z;
                line_string_stream >>c_red;
                line_string_stream >>c_green;
                line_string_stream >>c_blue;
                line_string_stream >>brightness;

                glm::vec3 pos{pos_x, pos_y, pos_z};
                Color color{c_red, c_green, c_blue};
                std::shared_ptr<Lichtquelle> pointer_cam = std::make_shared<Lichtquelle>(Lichtquelle{licht_name, pos, color,brightness});
                licht_vec.push_back(pointer_cam);
                my_Scene.lichtvec = licht_vec;
            }
            if("camera" == identifier){
                std::string cam_name;
                int degree;

                line_string_stream >> cam_name;
                line_string_stream >> degree;
                
                std::shared_ptr<Camera> pointer_cam = std::make_shared<Camera>(Camera{cam_name, degree});
                cam_vec.push_back(pointer_cam);
                my_Scene.camvec = cam_vec;
            }
        }
        if("render" == identifier){
            int x, y;
            line_string_stream >>x;
            line_string_stream >>y;
            my_Scene.res_x = x;
            my_Scene.res_y = y;
        }
    }
    return my_Scene;
}