
#include "fly.h"

int main(){

  fly::createWindow("parallelogram", 800, 600);
  fly::initialize(fly::projectionMethod::ORTHO);

  float vertices[] = {
    //x,   y, z, s, t
   -100, -50, 0, 0, 1,
      0,  50, 0, 0, 0,
    100,  50, 0, 1, 0,
      0, -50, 0, 1, 1
  };

  unsigned int indices[] = {

    0, 1, 3,
    3, 1, 2
  };

  fly::Thing parallelogram;
  parallelogram.initialize(vertices, sizeof(vertices), indices, sizeof(indices));

  fly::fill(1, 0.5, 0.5);

  for(; fly::running(); fly::update()){

    fly::translate(fly::width/2, fly::height/2);
    parallelogram.display();
  }

  fly::terminate();
  return 0;
}
