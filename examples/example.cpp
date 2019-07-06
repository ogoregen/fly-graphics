
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "shader.h"
#include "texture.h"
#include "thing.h"

int width = 800;
int height = 600;

void init(){

  if(!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(width, height, "opengl example", NULL, NULL);
  if(!window){

    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  if(glewInit() != GLEW_OK) return -1;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(void){

  shader basic("resources/shaders/basic_vs.shader", "resources/shaders/basic_fs.shader");
	basic.bind();

  glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

  texture yourtexture("textures/texture.png");
  thing yourthing(yourtexture.w, yourtexture.h);

  while(!glfwWindowShouldClose(window)){

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(300, 300, 0));
    basic.setUmat4f("mvp", proj * model);
    yourtexture.bind();
    yourthing.display();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
