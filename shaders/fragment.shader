
#version 330 core

out vec4 FragColor;

in vec2 textureC;

uniform sampler2D textureSampler;
uniform vec4 fillColor;
uniform bool usingTexture;

void main(){

  if(usingTexture) FragColor = texture(textureSampler, textureC);
  else FragColor = vec4(fillColor);
}

