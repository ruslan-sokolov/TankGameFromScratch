#shader vertex
#version 430 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;

void main()
{
    o_Color = v_Color;
}
