#version 420 core

layout(location = 0) out vec4 fragColor;

struct VertexOutput
{
    vec4 tint;
    vec2 texCoords;
    float texLayer;
    float texIndex;
};

layout(location = 0) in VertexOutput vertex;

layout(binding = 0) uniform sampler2DArray samplers[16];

void main()
{
    fragColor = vertex.tint * texture(samplers[int(vertex.texIndex)], vec3(vertex.texCoords, floor(vertex.texLayer)));
};