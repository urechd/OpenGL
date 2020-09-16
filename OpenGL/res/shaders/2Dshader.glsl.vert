#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_textCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * a_position;
    v_TextCoord = a_textCoord;
}