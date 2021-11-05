#version 410 core

layout (location =0) in vec3 position;
uniform mat4 MVP;
out vec4 out_color;

void main() {
	gl_Position = MVP * vec4(position,1.0);
	out_color = vec4(position.x + 0.5, 1.0, position.y + 0.5, 1.0);
}