#version 330 core

in vec4 vertex;
out vec2 texCoords;

uniform float depth;
uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * vec4(vertex.xy, depth, 1.0);
	texCoords = vertex.zw;
}