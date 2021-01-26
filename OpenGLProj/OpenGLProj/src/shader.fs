#version 330 core
out vec4 FragColor;

in vec2 myTex;

uniform sampler2D boxTex;
uniform sampler2D surTex;

void main()
{
    FragColor = mix(texture(boxTex, myTex), texture(surTex, myTex), 0.2); 
}