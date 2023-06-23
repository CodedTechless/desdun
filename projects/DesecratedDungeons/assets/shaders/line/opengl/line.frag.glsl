#version 420 core

layout(location = 0) out vec4 fragColor;

in vec4 tint;

void main()
{
    fragColor = tint;
};