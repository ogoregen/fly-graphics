
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 t_coord_;
layout (location = 2) in vec2 data;

out vec2 t_coord;
out float tint;

uniform mat4 mvp;

void main(){

	gl_Position = mvp * vec4(position.x + data.x, position.y + data.y, position.z, 1.0);
	tint = 1;
	t_coord = t_coord_;
}
