#shader vertex
#version 330 core

in vec3 Position;
in vec4 v_Tint;
in vec2 v_TextureCoordinate;
in uint v_Layer;
in uint v_TextureSlot;

out vec4 Tint;
out vec2 TextureCoordinate;
flat out uint Layer;
flat out uint TextureSlot;

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
#version 330 core

out vec4 FragColor;

in vec4 Tint;
in vec2 TextureCoordinate;
flat in uint Layer;
flat in uint TextureSlot;

uniform sampler2DArray Textures[16];

void main()
{
    FragColor = Tint * texture(Textures[TextureSlot], vec3(TextureCoordinate, Layer));
};