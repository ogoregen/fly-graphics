
#include "fly/fly.h"

int main(){

  fly::createWindow("parallelogram", 800, 600);
  fly::initialize(fly::projectionMethod::ORTHO);

  float vertices[] = {
    //x,   y, z
   -100, -50, 0,
      0,  50, 0,
    100,  50, 0,
      0, -50, 0
  };

  unsigned int indices[] = { //vertex draw order, as two triangles

    0, 1, 3,
    3, 1, 2
  };

  fly::Thing parallelogram;
  parallelogram.initialize(vertices, sizeof(vertices), indices, sizeof(indices), true);

  fly::fill(82, 9, 91); //rgb
  
  float angle = 0;
  
  for(; fly::running(); fly::update()){

    fly::translate(fly::width/2, fly::height/2);
    fly::rotate(0, 0, angle);
    parallelogram.display();
    angle++;
  }

  fly::terminate();
  return 0;
}

