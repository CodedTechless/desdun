#shader vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 tint;

out vec4 o_tint;

uniform mat4 projection;

void main()
{
    o_tint = tint;

    gl_Position = projection * vec4(position.xyz, 1.0);
};

#shader fragment
#version 420 core

layout(location = 0) out vec4 fragColor;

in vec4 tint;

void main()
{
    fragColor = Tint;
};