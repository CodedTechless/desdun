#version 330 core

layout(location = 0) out vec4 fragColor;

struct VertexOutput
{
    vec4 tint;
    vec2 texCoords;
    float texLayer;
    float texIndex;
};

in VertexOutput vertex;

uniform sampler2DArray samplers[16];

void main()
{
    vec4 color = vec4(0.0);
    vec3 coords = vec3(vertex.texCoords, vertex.texLayer);

    switch (int(vertex.texIndex))
    {
        case 0: color = texture(samplers[0], coords); break;
        case 1: color = texture(samplers[1], coords); break;
        case 2: color = texture(samplers[2], coords); break;
        case 3: color = texture(samplers[3], coords); break;
        case 4: color = texture(samplers[4], coords); break;
        case 5: color = texture(samplers[5], coords); break;
        case 6: color = texture(samplers[6], coords); break;
        case 7: color = texture(samplers[7], coords); break;
        case 8: color = texture(samplers[8], coords); break;
        case 9: color = texture(samplers[9], coords); break;
        case 10: color = texture(samplers[10], coords); break;
        case 11: color = texture(samplers[11], coords); break;
        case 12: color = texture(samplers[12], coords); break;
        case 13: color = texture(samplers[13], coords); break;
        case 14: color = texture(samplers[14], coords); break;
        case 15: color = texture(samplers[15], coords); break;
    }

    fragColor = vertex.tint * color;
};