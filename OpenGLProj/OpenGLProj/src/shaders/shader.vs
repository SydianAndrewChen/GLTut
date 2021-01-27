#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspProj;

out vec3 Pos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = perspProj * view * model * vec4(aPos,  1.0);
    Pos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTex;
}