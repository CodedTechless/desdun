#shader vertex
#version 420 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 v_Tint;
layout(location = 2) in vec2 v_TextureCoordinate;
layout(location = 3) in float v_Layer;
layout(location = 4) in float v_TextureSlot;

out vec4 Tint;
out vec2 TextureCoordinate;
flat out float Layer;
flat out float TextureSlot;

uniform mat4 Projection;

void main() 
{
    Tint = v_Tint;
    TextureCoordinate = v_TextureCoordinate;
    Layer = v_Layer;
    TextureSlot = v_TextureSlot;

    gl_Position = Projection * vec4(Position.xyz, 1.0);
};

#shader fragment
#version 420 core

layout(location = 0) out vec4 FragColor;

in vec4 Tint;
in vec2 TextureCoordinate;
flat in float Layer;
flat in float TextureSlot;

uniform sampler2DArray Textures[16];

void main()
{
    FragColor = Tint * texture(Textures[int(TextureSlot)], vec3(TextureCoordinate, floor(Layer)));
};