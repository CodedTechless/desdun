#shader vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_tint;

out vec4 tint;

uniform mat4 projection;

void main()
{
    tint = v_tint;

    gl_Position = projection * vec4(position, 1.0);
};

#shader fragment
#version 420 core

layout(location = 0) out vec4 fragColor;

in vec4 tint;

void main()
{
    fragColor = tint;
};