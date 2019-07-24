#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "scene.hpp"
#include <string>
#include <sstream>
TEST_CASE ("rec", "[rec]"){
  glm::vec3 origin {0.f, 0.f, 0.f};
  glm::vec3 corner1 {2.f, 2.f, 2.f};
  Color color{0.f, 0.f, 0.f};
  float z = 2;
  Material m1 = {"Holz", color, 0.f, 0.f, 0.f, 2};
  std::shared_ptr<Material> c1 = std::make_shared<Material>(Material{});
  Box b1 {origin,corner1,"KASTEN",c1};
  REQUIRE(b1.area()==16);
  REQUIRE(b1.volume()==8);

  std::cout<<b1;
}
TEST_CASE ("sph", "[sph]"){
  glm::vec3 origin {0.f, 0.f, 0.f};
  std::shared_ptr<Material> c1 = std::make_shared<Material>(Material{});
  Sphere s1 {origin, 4.f,"KREIS", c1};
  REQUIRE(round(s1.area())==201);
  REQUIRE(round(s1.volume())==268);
  std::cout<<s1;
}

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
TEST_CASE ("intersect_ray_sphere", "[intersect]")
{
  // Ray
  glm::vec3 ray_origin {0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized !
  // you can use :
  //v = glm::normalize (some_vector)
  glm::vec3 ray_direction{0.0f ,0.0f, 1.0f};
  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius {1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
  ray_origin, ray_direction ,
  sphere_center ,
  sphere_radius * sphere_radius , // squared radius !!!
  distance);
  REQUIRE(distance == Approx(4.0f));


  glm::vec3 origin {8.f, 0.f, 0.f};
  std::shared_ptr<Material> c1 = std::make_shared<Material>(Material{});
  Sphere s1 {origin, 5.f,"KREIS", c1};
  glm::vec3 rayo{0.0f, 0.0f, 0.0f};
  glm::vec3 rayd{1.f, 0.f, 0.f};
  Ray testray{rayo, rayd};
  float t = 2;
}


TEST_CASE ("delete", "[delete]")
{
  glm::vec3 origin {8.f, 0.f, 0.f};
  std::shared_ptr<Material> red = std::make_shared<Material>(Material{});
  Sphere* s1 =new Sphere{origin, 5.f,"sphere0", red};
  Shape* s2 =new Sphere{origin, 5.f,"sphere1", red};
  delete s1;
  delete s2;
}
TEST_CASE ("squareint", "[intersect]"){
  glm::vec3 origin {1.f, 1.f, 1.f};
  glm::vec3 corner1 {4.f, 4.f, 4.f};
  std::shared_ptr<Material> c1 = std::make_shared<Material>(Material{});
  Box b1 {origin,corner1,"BOX",c1};
  glm::vec3 rayo{0.0f, 0.0f, 0.0f};
  glm::vec3 rayd{1.f, 1.f, 1.f};
  glm::vec3 rayc{1.f, 0.f, 1.f};
  Ray testray2{rayo, rayc};
  Ray testray{rayo, rayd};
  float t = 1;
  REQUIRE(b1.intersect(testray, t).cut_);
  REQUIRE(!b1.intersect(testray2, t).cut_);
}
TEST_CASE ("tostruc", "[tostruc]"){
  std::string path = "/home/vincent/Dokumente/programmiersprachen-raytracer/source/material.sdf";
  Scene S {create(path)};
}
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
