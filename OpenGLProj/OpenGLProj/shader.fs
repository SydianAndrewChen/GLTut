#version 330 core
out vec4 FragColor;

in vec3 myColor;
in vec2 myTex;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, myTex) * vec4(myColor, 1.0); 
}