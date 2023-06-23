#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_tint;
layout(location = 2) in vec2 v_texCoords;
layout(location = 3) in float v_texLayer;
layout(location = 4) in float v_texIndex;

out vec4 tint;
out vec2 texCoords;
flat out float texLayer;
flat out float texIndex;

uniform mat4 projection;

void main() 
{
    tint = v_tint;
    texCoords = v_texCoords;
    texLayer = v_texLayer;
    texIndex = v_texIndex;

    gl_Position = projection * vec4(position, 1.0);
};