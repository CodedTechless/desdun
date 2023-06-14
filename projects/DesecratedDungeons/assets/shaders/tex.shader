#shader vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 tint;
layout(location = 2) in vec4 texdata;

out vec4 o_tint;
out vec2 o_texCoords;
flat out vec2 o_texData;

uniform mat4 projection;

void main() 
{
    o_tint = tint;
    o_texCoords = texdata.xy;
    o_texData = texdata.zw;

    gl_Position = projection * vec4(position.xyz, 1.0);
};

#shader fragment
#version 420 core

layout(location = 0) out vec4 fragColor;

in vec4 tint;
in vec2 texCoords;
flat in vec2 texData;

uniform sampler2DArray samplers[16];

void main()
{
    fragColor = tint * texture(samplers[int(texData.y)], vec3(texCoords, floor(texData.x)));
};