#version 420 core

layout(location = 0) out vec4 fragColor;

in vec4 tint;
in vec2 texCoords;
flat in float texLayer;
flat in float texIndex;

uniform sampler2DArray samplers[16];

void main()
{
    fragColor = tint * texture(samplers[int(texIndex)], vec3(texCoords, floor(texLayer)));
};