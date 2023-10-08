#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_tint;
layout(location = 2) in vec2 v_texCoords;
layout(location = 3) in float v_texLayer;
layout(location = 4) in float v_texIndex;

struct VertexOutput
{
    vec4 tint;
    vec2 texCoords;
    float texLayer;
    float texIndex;
};

out VertexOutput vertex;

uniform mat4 projection;

void main() 
{
    vertex.tint = v_tint;
    vertex.texCoords = v_texCoords;
    vertex.texLayer = v_texLayer;
    vertex.texIndex = v_texIndex;

    gl_Position = projection * vec4(position, 1.0);
};