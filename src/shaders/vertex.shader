
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 instancePosition;

out vec2 textureC;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){

  gl_Position = projection * view * model * vec4(position + instancePosition, 1.0);
  textureC = textureCoordinates;
}

