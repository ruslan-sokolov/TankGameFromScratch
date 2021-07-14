#shader vertex
#version 430 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;
loyout(location = 2) in float a_TextureSlot;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out float v_TextureSlot;

void main()
{
    v_TexCoord = a_TexCoord;
    v_TextureSlot = a_TextureSlot;
    gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in float v_TextureSlot;

uniform vec4 u_Color;
uniform sampler2D u_Textures[32];

void main()
{
    int index = int(v_TextureSlot);
    o_Color = texture(u_Textures[index], v_TexCoord) * u_Color;
}