// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene my_Scene)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
  , s_(my_Scene)
{}

void Renderer::render()
{
  float  my_start_x, my_start_y, my_start_z, my_height, my_width;   //Alles was ich brauche
  float distance = 10000.f;
  glm::vec3 my_origin{0.f, 0.f, 0.f};                           
  my_start_x = -0.5;                                              //ist festgelegt
  my_start_y = -0.5*cos(s_.camvec[0]->degree_);  
  my_start_z = -0.5*cos(s_.camvec[0]->degree_)*cos(s_.camvec[0]->degree_)/sin(s_.camvec[0]->degree_);    
  my_height = cos(s_.camvec[0]->degree_); 
  my_width = 1;
  

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Pixel p(x,y);
      
      int xt = x*s_.res_x/width_; //xt = der Pixel in zb 480 Auflösung der im ausgegebenen Bild angegeben werden 
      int yt = y*s_.res_y/height_; //Pixel auf Bildschirm zu Pixel in Auflösung
      glm::vec3 my_vec {(my_start_x + xt*my_width/s_.res_x), (my_start_y + yt*my_height/s_.res_y), my_start_z};
      Ray checker {my_origin, my_vec};    //Ray zum intersect test
      if(s_.boxvec[0]->intersect(checker, distance).cut_){   //Cut test-> color zuweisung von Box
        p.color = s_.boxvec[0]->intersect(checker, distance).color_->ka; 
      }
      if(s_.spherevec[0]->intersect(checker, distance).cut_){   //Cut test-> color zuweisung von Box
        p.color = s_.spherevec[0]->intersect(checker, distance).color_->ka; 
      }
      
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
