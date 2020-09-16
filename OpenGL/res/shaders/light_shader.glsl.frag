#version 330 core

out vec4 color;

in vec4 v_Color;
in vec4 v_Normal;
in vec4 v_FragPos;

uniform vec4 u_AmbientLightColor;
uniform vec4 u_DifuseLightColor;
uniform vec4 u_DiffuseLightPosition;

void main()
{
    float ambientStrength = 0.1;
    vec4 ambientLight = ambientStrength * u_AmbientLightColor;

    vec4 norm = normalize(v_Normal);
    vec4 diffuseLightDir = normalize(u_DiffuseLightPosition - v_FragPos);

    float diff = max(dot(norm, diffuseLightDir), 0.0);
    vec4 diffuseLight = diff * u_DifuseLightColor;

    vec4 result = (ambientLight + diffuseLight) * v_Color;
    color = result;
}