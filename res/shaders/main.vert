#version 410 core

layout (location =0) in vec4 position;
out vec4 out_color;

void main() {
	gl_Position = position;
	out_color = vec4(position.x + 0.5, 1.0, position.y + 0.5, 1.0);
}