#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform int u_EntityID;

void main()
{
	color = texture(u_Texture, v_TexCoord * 10.0) * u_Color;
	entityID = u_EntityID;
}
