#version 460

in vec3 LightIntensity;
layout (location = 0) out vec4 FragColor;

in vec3 color;


void main() {
    FragColor = vec4(LightIntensity, 1.0);
    FragColor = vec4(1.0, 0.0, 0.0, 1.0f);
}
