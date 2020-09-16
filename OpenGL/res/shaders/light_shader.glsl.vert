#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec4 a_normal;

out vec4 v_Color;
out vec4 v_Normal;
out vec4 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * a_position;
    v_Color = a_color;
    v_Normal = a_normal;
    v_FragPos = u_Model * a_position;
}