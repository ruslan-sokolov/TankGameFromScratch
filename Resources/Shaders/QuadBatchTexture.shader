#shader vertex
#version 330

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TextureSlot;

uniform mat4 u_ViewProjModel;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TextureSlot;

void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TextureSlot = a_TextureSlot;
    gl_Position = u_ViewProjModel * vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 330

layout(location = 0) out vec4 o_Color;

flat in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TextureSlot;

uniform sampler2D u_Textures[32];

void main()
{
	int Index = int(v_TextureSlot);
    o_Color = texture(u_Textures[Index], v_TexCoord) * v_Color;
	//o_Color = v_Color;
}
