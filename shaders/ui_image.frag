#version 330 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = texture(tex, texCoords);
    color = sampled;
} 