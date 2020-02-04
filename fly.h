
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fly{

enum class projectionMethod{ORTHO, PERSPECTIVE};

class Shader{

    unsigned int ID;

    std::string loadFile(const char* path){

      std::string output;
      std::ifstream reader;
      reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      try{

        reader.open(path);
        std::stringstream stream;
        stream << reader.rdbuf();
        reader.close();
        output = stream.str();
      }
      catch(std::ifstream::failure error){

        std::cout << "Shader reading error." << std::endl;
      }

      return output;
    }

  public:

    void load(const char* vsPath, const char* fsPath){

      unsigned int vertex, fragment;
      int success;
      char infoLog[512];

      std::string vs = loadFile(vsPath);
      std::string fs = loadFile(fsPath);
      const char* vsSource = vs.c_str();
      const char* fsSource = fs.c_str();

      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vsSource, NULL);
      glCompileShader(vertex);
      glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
      if(!success){

        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation error." << std::endl /* << infoLog << std::endl */;
      }

      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fsSource, NULL);
      glCompileShader(fragment);
      glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
      if(!success){

        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation error." << std::endl /* << infoLog <<  std::endl */;
      }

      ID = glCreateProgram();
      glAttachShader(ID, vertex);
      glAttachShader(ID, fragment);
      glLinkProgram(ID);
      glGetProgramiv(ID, GL_LINK_STATUS, &success);
      if(!success){

        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Shader linking error." << std::endl /* << infoLog << std::endl */;
      }

      glDeleteShader(vertex);
      glDeleteShader(fragment);
    }

    void bind(){

	    glUseProgram(ID);
    }

    void setUniform(const std::string &name, bool value) const{

	    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setUniform(const std::string &name, int value) const{

      glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniform(const std::string &name, float value) const{

      glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniform(const std::string &name, const glm::vec2 &value) const{

      glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setUniform(const std::string &name, const glm::vec3 &value) const{

  	  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setUniform(const std::string &name, const glm::vec4 &value) const{

      glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setUniform(const std::string &name, const glm::mat2 &value) const{

      glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setUniform(const std::string &name, const glm::mat3 &value) const{

      glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setUniform(const std::string &name, const glm::mat4 &value) const{

      glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    ~Shader(){
      
      glDeleteProgram(ID);
    }
};

class Texture{

		unsigned int ID;

	public:

		void load(const char* path){

      glGenTextures(1, &ID);
      glBindTexture(GL_TEXTURE_2D, ID);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      int width, height, channelCount;
      stbi_set_flip_vertically_on_load(true);
      unsigned char* data = stbi_load(path, &width, &height, &channelCount, 0);
      if(data){

        if(channelCount == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if(channelCount == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
      }
      else std::cout << "Failed to load texture." << std::endl;
      glBindTexture(GL_TEXTURE_2D, 0);
      stbi_image_free(data);
    }

		void bind(){

      glBindTexture(GL_TEXTURE_2D, ID);
    }

		~Texture(){

      glDeleteTextures(1, &ID);
    }
};

class Thing{

    unsigned int vao = 0, elementCount = 0, count = 0;
		bool textureSet = false;
		Texture *texture = nullptr;

  public:

		void initialize(float vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount, bool noTextureCoordinates = false){

      count = 1;
      elementCount = indexCount;
      unsigned int componentCount;

      if(noTextureCoordinates) componentCount = 3;
      else componentCount = 5;

      unsigned int vbo, ebo;
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glGenBuffers(1, &ebo);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), &vertices[0], GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, componentCount * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      if(!noTextureCoordinates){

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, componentCount * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
      }

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      glDeleteBuffers(1, &vbo);
      glDeleteBuffers(1, &ebo);
    }

		void setTexture(const char *path){

      texture = new Texture;
      texture->load(path);
      textureSet = true;
    }

    void instance(glm::vec3 positions[], unsigned int count_){

      count = count_;

      if(count != 0){

        unsigned int vbo2;
        glGenBuffers(1, &vbo2);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(2, 1);
        glBindVertexArray(0);

        glDeleteBuffers(1, &vbo2);
      }
    }

		void display(){

      if(textureSet) texture->bind();
      glBindVertexArray(vao);
      if(count == 1) glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
      else if(count > 1) glDrawElementsInstanced(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0, count);
    }

    ~Thing(){

      glDeleteVertexArrays(1, &vao);
    }
};

projectionMethod method;
GLFWwindow *window;
Shader basicShader;
glm::mat4 projection, view, model;
float near, far, fieldOfView;
double mouseX, mouseY;
int width, height;

//graphics below

void background(float r, float g = 0, float b = 0, float a = 1){

  glClearColor(r, g, b, a);
}

void fill(float r = -1, float g = -1, float b = -1, float a = 1){ //calling with no parameters to enables textures 

  if(r != -1){

    basicShader.setUniform("usingTexture", false);
    basicShader.setUniform("fillColor", glm::vec4(r, g, b, a));
  }
  else basicShader.setUniform("usingTexture", true);
}

void translate(float x, float y, float z = 0){

  model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  basicShader.setUniform("model", model);
}

void rotate(float x, float y, float z = 0){

  model = glm::rotate(model, glm::radians(x), glm::vec3(1, 0, 0));
  model = glm::rotate(model, glm::radians(y), glm::vec3(0, 1, 0));
  model = glm::rotate(model, glm::radians(z), glm::vec3(0, 0, 1));
  basicShader.setUniform("model", model);
}

void camera(float x, float y, float z, float centerX, float centerY, float centerZ){

  view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(centerX, centerY, centerZ), glm::vec3(0, -1, 0));
  basicShader.setUniform("view", glm::mat4(1));
}

//base below

void onResize(GLFWwindow *window, int width_, int height_){

  width = width_;
  height = height_;
  glViewport(0, 0, width, height);
  if(method == projectionMethod::ORTHO) projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
  else if(method == projectionMethod::PERSPECTIVE) projection = glm::perspective(glm::radians(fieldOfView), (float)width / (float)height, near, far);
  basicShader.setUniform("projection", projection);
}

void createWindow(const char *title, int width_ = 0, int height_ = 0){ //fullscreen if width and height are unspecified or 0

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(width_ == 0 || height_ == 0){

    int xPosition, yPosition, monitorWidth, monitorHeight;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xPosition, &yPosition, &monitorWidth, &monitorHeight);
    width = monitorWidth;
    height = monitorHeight;
    window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
  }
  else{

    width = width_;
    height = height_;
    window = glfwCreateWindow(width, height, title, NULL, NULL);
  }

  if(window == NULL){

    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to initialize GLAD." << std::endl;
}

void initialize(projectionMethod method_, float near_ = 0.1, float far_ = 10000, float fov = 45){

  method = method_;
  fieldOfView = fov;
  near = near_;
  far = far_;

  glfwSetFramebufferSizeCallback(window, onResize);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  basicShader.load("shaders/vertex.shader", "shaders/fragment.shader");
  basicShader.bind();

  if(method == projectionMethod::ORTHO) projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, near, far);
  else if(method == projectionMethod::PERSPECTIVE) projection = glm::perspective(glm::radians(fieldOfView), (float)width/(float)height, near, far);
  basicShader.setUniform("projection", projection);

  background(0);
  camera(0, 0, 0, 0, 0, 0);
}

bool running(){

  return !glfwWindowShouldClose(window);
}

void update(){

  glfwGetCursorPos(window, &mouseX, &mouseY);
  glfwSwapBuffers(window);
  glfwPollEvents();
  translate(0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void terminate(){

  glfwTerminate();
}

//general utility below

double map(double x, double r1, double r2, double a1, double a2){

  double p = (r2 - r1) / (x - r1);
  double y = ((a2 - a1) / p) + a1;
  return y;
}

}

